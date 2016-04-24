/*Author: Zane Draper
 * 
 *Purpose: Creates the static variables for entire game
 *
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MileStone4
{
    public static class GameVariables //consistent variables need throughout game
    {
        public static int GameWidth = 800;
        public static int GameHeight = 600;
        public static int InnerWidth = 800;
        public static int InnerHeight = 600;
        public static int TankSpeed = 5;
        public static int BulletSpeed = 10;
        public static string WallImage = "Wall.png";
        public static string BulletImage = "Bullet.png";
        public static string RedTankUpImage = "RedTankUp.png";
        public static string RedTankRightImage = "RedTankRight.png";
        public static string RedTankDownImage = "RedTankDown.png";
        public static string RedTankLeftImage = "RedTankLeft.png";
        public static string GreenTankUpImage = "GreenTankUp.png";
        public static string GreenTankRightImage = "GreenTankRight.png";
        public static string GreenTankDownImage = "GreenTankDown.png";
        public static string GreenTankLeftImage = "GreenTankLeft.png";
    }
}
