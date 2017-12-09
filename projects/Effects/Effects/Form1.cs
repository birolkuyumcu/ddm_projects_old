using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Effects program;
        bool FirstTime = true;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            program = new Effects();                 

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (program.OpenWebCam()) 
            {
                timer1.Interval = 10;
                timer1.Enabled = true;
                button2.Enabled = true;

            }


        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            pictureBox1.Image = program.GetFrame();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            program.efect = Efect.Normal;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            program.efect = Efect.Gray;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            program.efect = Efect.Canny;
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            program.efect = Efect.Erode;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (FirstTime==false)
            {
                program.StartStopRecording();
                if (program.Recording)
                    button2.Text = "Recording !";
                else
                    button2.Text = "Paused";
            }
            else
            {
                if (saveFileDialog1.ShowDialog()== DialogResult.OK)
                {
                    if (program.InitRecording(saveFileDialog1.FileName))
                    {
                        FirstTime = false;
                        button2.Text = "Recording !";                
                    }

                }
            }


        }

    }
}
