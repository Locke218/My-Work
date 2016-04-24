/*Author: Zane Draper
 * 
 *Purpose: Creates the bullet and all its attributes.
 *
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace MileStone4
{
    class Bullet: MovableGamePiece //constructor
    {
        //attributes
        private bool active;

        //properties
        public bool Active { get { return active; } set { active = value; } }

        //constructor uses base constructor to set location
        public Bullet() : base(0, 0, GameVariables.BulletImage) { active = false; Image.Visible = false; }

        public override void Move()
        {
            if (active == true) //only moves if active
            {
                switch (Direction) //moves in the direction set by tank
                {
                    case 0:
                        if (Y > 0)
                            Y -= GameVariables.BulletSpeed;
                        break;
                    case 1:
                        if (PosValues.Right < GameVariables.InnerWidth - 1) //fulll width is outside range
                            X += GameVariables.BulletSpeed;
                        break;
                    case 2:
                        if (PosValues.Bottom < GameVariables.InnerHeight - 1)//full height is outside range
                            Y += GameVariables.BulletSpeed;
                        break;
                    case 3:
                        if (X > 0)
                            X -= GameVariables.BulletSpeed;
                        break;
                }

                if (PosValues.X < 0 || PosValues.X > GameVariables.InnerWidth - 1 || PosValues.Y < 0 || PosValues.Y > GameVariables.InnerHeight - 1) //if it would move out of frame, its reset
                {
                    active = false; //resets
                }
            }
        }

        public override void Draw() //only visible if active
        {
            if (active == true)
            {
                base.Draw();
                Image.Visible = true;
            }
            else
                Image.Visible = false;
        }

        //overrides to add type and if active
        public override string ToString()
        {
            return "Bullet: Active: " + active.ToString() + " " + base.ToString();
        }
    }
}
