/*Author: Zane Draper
 * 
 *Purpose: Creates the base game piece and attributes
 *
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace MileStone4
{
    public abstract class GamePiece
    {
        //attributes
        public Rectangle posValues;
        private PictureBox image;

        //properties
        public Rectangle PosValues { get { return posValues; } set { posValues = value; } }
        public int X { get { return posValues.X; } set { posValues.X = value; } } //makes the location variables accesible
        public int Y { get { return posValues.Y; } set { posValues.Y = value; } }
        public PictureBox Image { get { return image; } set { image = value; } }

        //constructor that sets location for all inheriting classes
        public GamePiece(int X, int Y, string imgFile)
        {
            image = new PictureBox();
            image.Location = new Point(X, Y);
            image.SizeMode = PictureBoxSizeMode.AutoSize;
            image.BorderStyle = BorderStyle.FixedSingle;
            image.Image = new Bitmap(imgFile);
            posValues = new Rectangle(image.Location, image.Size);
        }

        //virtual method for presenting visual output location of all game pieces
        public virtual void Draw()
        {
            Image.Location = new Point(PosValues.X, PosValues.Y);
        }

        public bool isColliding(GamePiece collider)//checks for rectangle intersection
        {
            if (PosValues.IntersectsWith(collider.PosValues))
            {
                return true;
            }
            else return false;
        }

        //override to show location
        public override string ToString()
        {
            return "Position: " + PosValues.X + ", " + PosValues.Y;
        }
    }
}
