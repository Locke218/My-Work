/*Author: Zane Draper
 * 
 *Purpose: Creates the tanks and attributes
 *
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MileStone4
{
    class Tank : MovableGamePiece
    {
        //attributes
        private int health;
        private Player owner;
        private Bullet tankBullet;
        private Bitmap[] tankImages;

        //properties
        public int Health { get { return health; } set { health = value; } }
        public Player Owner { get { return owner; } set { ;} }
        public Bullet TankBullet { get { return tankBullet; } set { ;} }

        //constuctor uses base constructor, sets owner and bullet object
        public Tank(Player player, Bullet bullet, int x, int y)
            : base(x, y, GameVariables.RedTankDownImage)
        {
            owner = player;
            tankBullet = bullet;
            health = 2;
            tankImages = new Bitmap[4];
            ImgArrayFiller();
        }

        public void ImgArrayFiller() //easier method to call to set images
        {
            if (owner.PlayerNumber == 1)
            {
                tankImages[0] = new Bitmap(GameVariables.RedTankUpImage);
                tankImages[1] = new Bitmap(GameVariables.RedTankRightImage);
                tankImages[2] = new Bitmap(GameVariables.RedTankDownImage);
                tankImages[3] = new Bitmap(GameVariables.RedTankLeftImage);
            }
            else if (owner.PlayerNumber == 2)
            {
                tankImages[0] = new Bitmap(GameVariables.GreenTankUpImage);
                tankImages[1] = new Bitmap(GameVariables.GreenTankRightImage);
                tankImages[2] = new Bitmap(GameVariables.GreenTankDownImage);
                tankImages[3] = new Bitmap(GameVariables.GreenTankLeftImage);
            }
        }

        //when tank takes hit, called to increment health down 1;
        public void TakeHit()
        {
            health--;
            if (IsDead())//handles if current tank has taken two hits
            {
                owner.LoseTank();
                health = 2;
            }
        }

        //called to check if tank has taken 2 or more hits, if so, returns true
        public bool IsDead()
        {
            if (health <= 0)
            {
                if (owner.PlayerNumber == 1) //resets location on death
                {
                    X = 10;
                    Y = 250;
                    Direction = 1;
                }
                else
                {
                    X = 650;
                    Y = 250;
                    Direction = 3;
                }
                return true;
            }
            else
                return false;
        }



        public override void Move()
        {
            switch (Direction)//moves specified units direction chosen by key press each time
            {
                case 0:
                    if (Y > 0)
                        Y -= GameVariables.TankSpeed;
                    break;
                case 1:
                    if (PosValues.Right < GameVariables.InnerWidth - 1) //fulll width is outside range
                        X += GameVariables.TankSpeed;
                    break;
                case 2:
                    if (PosValues.Bottom < GameVariables.InnerHeight - 1)//full height is outside range
                        Y += GameVariables.TankSpeed;
                    break;
                case 3:
                    if (X > 0)
                        X -= GameVariables.TankSpeed;
                    break;
            }
        }

        public void Reverse()
        {
            switch (Direction)//moves set positions in opposite direction chosen by key press each time object is intersected
            {
                case 0:
                    if (PosValues.Y > 0)
                        Y += GameVariables.TankSpeed;
                    break;
                case 1:
                    if (PosValues.X < GameVariables.InnerWidth - 1) //fulll width is outside range
                        X -= GameVariables.TankSpeed;
                    break;
                case 2:
                    if (PosValues.Y < GameVariables.InnerHeight - 1)//full height is outside range
                        Y -= GameVariables.TankSpeed;
                    break;
                case 3:
                    if (PosValues.X > 0)
                        X += GameVariables.TankSpeed;
                    break;
            }
        }
        public override void Draw()
        {
            Image.Image = tankImages[Direction];
            base.Draw(); // set location
        }

        public void Fire() //if bullet is not active, it is set active and updated;
        {
            if (tankBullet.Active != true)
            {
                tankBullet.Direction = this.Direction; //copies tank direction
                tankBullet.PosValues = new Rectangle(new Point(PosValues.X + PosValues.Width / 2, PosValues.Y + PosValues.Height / 2), tankBullet.PosValues.Size);
                tankBullet.Active = true;
            }
        }

        //override to add type and health
        public override string ToString()
        {
            return "Tank: Health: " + health.ToString() + " " + base.ToString();
        }
    }
}
