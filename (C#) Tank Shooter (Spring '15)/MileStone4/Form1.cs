/*Author: Zane Draper
 * 
 *Purpose: Creates the first screen and draws to it
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
    public partial class InfoForm : Form
    {
        public InfoForm() //constuctor
        {
            InitializeComponent();
        }

        private void btnClear_Click(object sender, EventArgs e) //clears the textboxes when clicked
        {
            nameBox1.Clear();
            nameBox2.Clear();
            mapFile.Clear();
        }

        private void btnPlay_Click(object sender, EventArgs e) //checks values in boxes before launching new form
        {
            const string caption = "Error"; //avoiding try blocks
            if (nameBox1.Text != "") //makes sure not empty
            {
                if (nameBox2.Text != "")
                {
                    if (File.Exists(mapFile.Text)) //if file exists, luanches new form, hides this one
                    {
                        GameForm gameForm = new GameForm(this, nameBox1.Text, nameBox2.Text, mapFile.Text);
                        gameForm.Show();
                        this.Hide();
                    }
                    else //error messages
                    {
                        const string message = "File Name is invalid";
                        var result = MessageBox.Show(message, caption,
                                                     MessageBoxButtons.OK,
                                                     MessageBoxIcon.Exclamation);
                    }
                }
                else
                {
                    const string message = "Player 2 Name is invalid";
                    var result = MessageBox.Show(message, caption,
                                                 MessageBoxButtons.OK,
                                                 MessageBoxIcon.Exclamation);
                }
            }
            else
            {
                const string message = "Player 1 Name is invalid";
                var result = MessageBox.Show(message, caption,
                                             MessageBoxButtons.OK,
                                             MessageBoxIcon.Exclamation);
            }
        }
    }
}
