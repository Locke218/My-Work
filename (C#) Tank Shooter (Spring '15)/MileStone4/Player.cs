/*Author: Zane Draper
 * 
 *Purpose: Creates the player
 *
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MileStone4
{
    class Player
    {
        //attributes
        private String name;
        private int lostTanks;
        private int playerNumber;
        static int playerCount = 0; //can be incremented in class whenever new player is added.
        //in case more then two are ever needed or other reasons, simpler to increment I.M.O.

        //properties
        public String Name { get { return name; } set { name = value; } }
        public int LostTanks { get { return lostTanks; } set { lostTanks = value; } }
        public int PlayerNumber { get { return playerNumber; } set { playerNumber = value; } }

        //constuctor sets variables, except playerCount because its static
        public Player(String namer)
        {
            name = namer;
            lostTanks = 0;
            playerNumber = ++playerCount;
        }

        //called to see if 5 or more tanks have been lost, if so, player loses
        public bool LostGame()
        {
            if (lostTanks >= 5) return true;
            else return false;
        }

        //called to increment number of lost tanks
        public void LoseTank()
        {
            lostTanks++;
        }

        //override to display player number, name, number of lost tanks
        public override string ToString()
        {
            return "Player #" + playerNumber.ToString() + " Name: " + name + " Tanks Lost: " + lostTanks.ToString();
        }
    }
}
