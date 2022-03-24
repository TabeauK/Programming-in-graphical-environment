using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsLab1
{
    public partial class Form1 : Form
    {
        int[] tab;
        bool game;
        bool start;
        int tick;
        Button selected;
        Random rand;
        int left;
        public Form1()
        {
            left = 8;
            rand = new Random();
            tab = new int[] { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7 };
            tick = 0;
            game = false;
            start = false;
            selected = null;
            InitializeComponent();
            create_tab();
        }


        private void button_Click(object sender, EventArgs e)
        {
            if (game)
            {
                if (selected == null)
                {
                    ((Button)sender).BackColor = Color.IndianRed;
                    selected = (sender as Button);
                }
                else if(selected !=null && selected.Text!=(sender as Button).Text)
                {
                    selected.BackColor = Color.AliceBlue;
                    selected = null;
                }
                else if (selected != null && selected.Text == (sender as Button).Text && (sender as Button) == selected)
                {
                    selected.BackColor = Color.AliceBlue;
                    selected = null;
                    
                }
                else if (selected != null && selected.Text == (sender as Button).Text && (sender as Button)!=selected)
                {
                    selected.Visible = false;
                    (sender as Button).Visible = false;
                    selected = null;
                    left--;
                    if(left==0)
                    {
                        var elem = MessageBox.Show($"Your time: {tick / 10} s. Do you want to play again?", "The End", MessageBoxButtons.YesNo);
                        if(elem == DialogResult.No)
                        {
                            Close();
                        }
                        Reset_Click(sender, e);
                    }
                }
            }
        }

        private void Start_Click(object sender, EventArgs e)
        {
            if (!start)
            {
                game = true;
                start = true;
                (sender as Button).Text = "Pause";
                timer.Start();

            }
            else
            {
                if(!game)
                {
                    game = true;
                    timer.Start();
                }
                else
                {
                    timer.Stop();
                    game = false;
                }
            }
        }

        private void Reset_Click(object sender, EventArgs e)
        {
            timer.Stop();
            Start.Text = "Start";
            game = false;
            start = false;
            tick = 0;
            label.Text = "0 s";
            foreach (Button elem in table.Controls)
            {
                elem.BackColor = Color.AliceBlue;
                elem.Visible = true;
            }
            create_tab();
            left = 8;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            tick++;
            if (tick % 10 == 0)
            {
                
                label.Text = (tick/10).ToString() + " s";
            }
        }

        private void create_tab()
        {
            tab = tab.OrderBy(r => rand.Next()).ToArray();
            int i = 0;
            foreach(Button elem in table.Controls)
            {
                elem.Text = tab[i].ToString();
                i++;
            }

        }
    }
}
