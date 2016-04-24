/*Author: Zane Draper
 * 
 *Purpose: Creates the screen and draws to it
 *
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace MileStone4
{
    public partial class GameForm : Form
    {
        //all 8 attributes
        public InfoForm infoForm;
        private Player player1;
        private Player player2;
        private Bullet bullet1;
        private Bullet bullet2;
        private Tank tank1;
        private Tank tank2;
        private List<Wall> walls;
        private Boolean gameOver; //no property because no outside access

        //all 7 properties
        internal Player Player1
        {
            get { return player1; }
            set { ; }
        }
        internal Player Player2
        {
            get { return player2; }
            set { ; }
        }
        internal Bullet Bullet1
        {
            get { return bullet1; }
            set { ; }
        }
        internal Bullet Bullet2
        {
            get { return bullet2; }
            set { ; }
        }
        internal Tank Tank1
        {
            get { return tank1; }
            set { ; }
        }
        internal Tank Tank2
        {
            get { return tank2; }
            set { ; }
        }
        internal List<Wall> Walls
        {
            get { return walls; }
            set { ; }
        }

        public GameForm()
        {
            InitializeComponent();
        }

        public GameForm(InfoForm infoForm, String name1, String name2, String fileName)//initiallizes components
        {
            InitializeComponent();

            this.infoForm = infoForm;

            player1 = new Player(name1);
            player2 = new Player(name2);
            bullet1 = new Bullet();
            bullet2 = new Bullet();
            tank1 = new Tank(player1, bullet1, 10, 10);
            tank2 = new Tank(player2, bullet2, 24, 4);
            walls = new List<Wall>();

            gameOver = false; //keeps game loop active

            ReadMap(fileName); //reads in info

            this.Size = new Size(GameVariables.GameWidth, GameVariables.GameHeight); //resizes
            GameVariables.InnerWidth = this.ClientSize.Width;
            GameVariables.InnerHeight = this.ClientSize.Height;

            Controls.Add(bullet1.Image); //adding these to screen
            Controls.Add(bullet2.Image);
            Controls.Add(tank1.Image);
            Controls.Add(tank2.Image);
            foreach (Wall wall in walls)
            {
                Controls.Add(wall.Image);
            }

            timer1.Start();
            GameLoop(); //initialize everything
        }
        

        //called when q is keyed in, ends game
        public void EndGame()
        {
            const string caption = "Error";
            string endMsg;
            
            if (player1.LostGame()) //personallizes the message
            {
                endMsg  = "PLAYER2 - WINNER!!";
            }
            else if (player2.LostGame())
            {
                endMsg = "PLAYER1 - WINNER!!";
            }
            else
            {
                endMsg = "NO WINNER!!";
            }
            //show message
            var result = MessageBox.Show(endMsg, caption,
                                         MessageBoxButtons.OK,
                                         MessageBoxIcon.Exclamation);
            this.Close(); //returns to original form
        }

        public void DrawGame()
        {
            tank1.Draw(); //updates object locations
            tank2.Draw();
            bullet1.Draw();
            bullet2.Draw();
            foreach (Wall w in walls)
            {
                w.Draw();
            }
        }

        private void DetectCollisions() //detects interaction between drawn objects
        {
            if ((tank1.isColliding(bullet2)) && bullet2.Active == true) //tank-bullet interaction
            {
                tank1.TakeHit(); //damages tank
                bullet2.Active = false; //resets bullet
            }
            if ((tank2.isColliding(bullet1)) && bullet1.Active == true)//the boolean was needed to keep an inactive unfired bullet from continually damaging the tank
            {
                tank2.TakeHit();
                bullet1.Active = false;
            }
            foreach (Wall k in walls) //cycles through all wall-bullet/tank collisions
            {
                if (k.isColliding(bullet1))
                {
                    bullet1.Active = false; //bullet is reset
                }
                if (k.isColliding(bullet2))
                {
                    bullet2.Active = false;
                }
                if (k.isColliding(tank1))
                {
                    tank1.Reverse(); //tank is unable to pass through
                }
                if (k.isColliding(tank2))
                {
                    tank2.Reverse();
                }
            }
        }

        //entire game runs through this, when this method ends, game ends
        public void GameLoop()
        {
            bullet1.Move(); //bullets have to move independently
            bullet2.Move();
            DetectCollisions(); //calls object interactions
            DrawGame(); //draws everything

            this.Text = tank1.Image.Location.X + "      Player 1: " + player1.Name + "Lost Tanks: " + player1.LostTanks + " Tank Health: " + tank1.Health + " Player 2: " + player2.Name + " Lost Tanks: " + player2.LostTanks + " Tank Health: " + tank2.Health;

            if (player1.LostGame() || player2.LostGame() || gameOver == true) //checks for winner
            {
                timer1.Stop();
                EndGame(); //finishes
            }
        }

        private void SetupTank(string tankInfo, Tank tankObj) //reads tank info from file, moves tank to appropriate place
        {
            try //tries to parse and place the tank
            {
                string[] info = tankInfo.Split(',');
                int[] infoInt = new int[3];
                int i = 0;

                foreach (string n in info)
                    {
                        infoInt[i] = int.Parse(n); //parsing sting
                        i++;
                    }

                tankObj.PosValues = new Rectangle(new Point(infoInt[0], infoInt[1]), tankObj.PosValues.Size);//setting up tank
                tankObj.Direction = infoInt[2];
            }
            catch // there are many possible exceptions, so this covers them all and puts the tanks in a usable location
            {
                if (tankObj.Owner.PlayerNumber == 1)
                {
                    tankObj.PosValues = new Rectangle(new Point(6, 11), tankObj.PosValues.Size);//setting up tank
                    tankObj.Direction = 1;
                }
                else if (tankObj.Owner.PlayerNumber == 2)
                {
                    tankObj.PosValues = new Rectangle(new Point(38, 11), tankObj.PosValues.Size);//setting up tank
                    tankObj.Direction = 3;
                }
            }
        }

        private void CreateWall(string wallInfo)
        {
            try //many errors possible
            {
                string[] info = wallInfo.Split(','); //splits string
                if (info.Length == 2) //makes sure of proper amount of info
                {
                    int[] infoInt = new int[2];
                    int i = 0;

                    foreach (string n in info)
                    {
                        infoInt[i] = int.Parse(n); //converts to int
                        i++;
                    }
                    walls.Add(new Wall(infoInt[0], infoInt[1]));

                }
                else return;
            }
            catch //exits without printing to screen
            {
                
            }
        }

        public void ReadMap(string mapLoc)//if error in single line, this allows the program to skip that
        {
            try
            {
                StreamReader stream = new StreamReader(mapLoc); //accesses the file

                SetupTank(stream.ReadLine(), tank1); //reads in tank info
                SetupTank(stream.ReadLine(), tank2);
                while (true)
                {
                    string input;
                    if ((input = stream.ReadLine()) != null)
                    {
                        CreateWall(input); //reads in wall info, if any
                    }
                    else
                        break;
                }
            }
            catch
            {
                SetupTank(null, tank1); //if there is an error with the file, the SetupTank method can still place them in default location
                SetupTank(null, tank2);
            }
        }

        private void GameForm_FormClosed(object sender, FormClosedEventArgs e) //fires when the form is closed
        {
            infoForm.Show();
        }

        private void GameForm_KeyPress(object sender, KeyPressEventArgs e) //watches for keys
        {
            switch (e.KeyChar)
            {
                case 'q': //ends game
                    gameOver = true;
                    break;
                case 'w': //next five move/fire tank 1
                    tank1.Direction = 0;
                    tank1.Move();
                    break;
                case 'a':
                    tank1.Direction = 3;
                    tank1.Move();
                    break;
                case 's':
                    tank1.Direction = 2;
                    tank1.Move();
                    break;
                case 'd':
                    tank1.Direction = 1;
                    tank1.Move();
                    break;
                case 'f':
                    tank1.Fire();
                    break;
                case 'i': //next five move/fire tank 2
                    tank2.Direction = 0;
                    tank2.Move();
                    break;
                case 'j':
                    tank2.Direction = 3;
                    tank2.Move();
                    break;
                case 'k':
                    tank2.Direction = 2;
                    tank2.Move();
                    break;
                case 'l':
                    tank2.Direction = 1;
                    tank2.Move();
                    break;
                case 'h':
                    tank2.Fire();
                    break;
            }

            DetectCollisions(); //checks for intersection in between each key press

        }

        private void timer1_Tick(object sender, EventArgs e) //updates game each tick
        {
            GameLoop();
        }
    }
}
