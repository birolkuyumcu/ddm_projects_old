using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace OposSharp
{
   

    public partial class Form1 : Form
    {
        Opos opos= new Opos(); 

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog op = new OpenFileDialog();
            op.Title = "Select Image File";
            op.FileName="*.jpg";
            if (op.ShowDialog() == DialogResult.OK) 
            {
                if (opos.LoadImage(op.FileName))
                {
                    pictureBox1.Image = opos.src.ToBitmap();
                    button2.Enabled = true;
                    numericUpDown1.Enabled = false;
                    numericUpDown1.Value = 1;
                    pictureBox2.Image = null;
                    listBox1.Items.Clear();
                }
            }


        }

        private void button2_Click(object sender, EventArgs e)
        {
            
            opos.PreProcess();
            int n=opos.FindPlates();
            if (n == 0) return;
            opos.ReadPlates();
            listBox1.Items.Clear();
            foreach (var s in opos.plakaList)
                listBox1.Items.Add(s);

            pictureBox1.Image = opos.src.ToBitmap();
            numericUpDown1.Enabled = true;
            numericUpDown1.Maximum = n;
            numericUpDown1.Value = 1;
            pictureBox2.Image = opos.plaka[0].ToBitmap();

        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            pictureBox2.Image = opos.plaka[(int)numericUpDown1.Value-1].ToBitmap();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            if (!File.Exists(opos.OcrName)) 
            {
                OpenFileDialog ocrf = new OpenFileDialog();
                ocrf.Title = "Show OCR File";
                ocrf.FileName = "gocr.exe";
                if (ocrf.ShowDialog() == DialogResult.OK)
                {
                    opos.OcrName = ocrf.FileName;
                }
                else
                    Application.Exit();
            
            }
                

        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://derindelimavi.blogspot.com/");
        }
    }
}
