using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using OpenCvSharp;
using OpenCvSharp.CPlusPlus;



namespace WindowsFormsApplication1
{
    struct Feature
    {
        public Point LeftEye;
        public Point RightEye;
        public Point Nose;
        public Point Mouth;
        public string ToString() 
        {
            string s;
            s = LeftEye.X.ToString() + " " + LeftEye.Y.ToString() + " : "
                + RightEye.X.ToString() + " " + RightEye.Y.ToString() + " : "
                + Nose.X.ToString() + " " + Nose.Y.ToString() + " : "
                + Mouth.X.ToString() + " " + Mouth.Y.ToString();
            return s;
        }
        public void Clear() 
        {
            LeftEye = new Point(0, 0);
            RightEye = new Point(0, 0);
            Nose = new Point(0, 0);
            Mouth = new Point(0, 0);        

        }


    }
    
    
    public partial class Form1 : Form
    {
        Extract ex;
        Feature ft=new Feature();
        bool imageOpened = false;
        bool facesExtracted = false;
        public Form1()
        {
            string fname = "haarcascade_frontalface_alt2.xml";
            if (File.Exists(fname) == false)
            {
                 OpenFileDialog op = new OpenFileDialog();
                 op.Filter = "HaarCascade Files (*.xml)|*.xml";
                 if (op.ShowDialog() == DialogResult.OK)
                     fname = op.FileName;
                 else
                     Application.Exit();
                 

            }
            ex = new Extract(fname);
            InitializeComponent();
        }

 
                
        private void pictureBoxClick(object sender, MouseEventArgs e)
        {
            if (facesExtracted == false) return;

            Point p = Control.MousePosition;
            p.X = e.X/4;
            p.Y = e.Y/4;
            switch (comboBox1.SelectedIndex) 
            {
                case 0: ft.LeftEye = p;
                    break;
                case 1: ft.RightEye = p;
                    break;
                case 2: ft.Nose = p;
                    break;
                case 3: ft.Mouth = p;
                    break;           
            
            }
            textBox1.Text = p.ToString();
            textBox2.Text = textBox1.Text;
            if (comboBox1.SelectedIndex != 3)
                comboBox1.SelectedIndex++;
            
            

        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            pictureBox1.Image = ex[(int) numericUpDown1.Value].ToBitmap();
            comboBox1.SelectedIndex = 0;
            ft.Clear();
            
        }

        private void openImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog op = new OpenFileDialog();
            op.Filter = "Image Files (*.jpg; *.bmp; *.png )|*.jpg; *.bmp; *.png";
            if (op.ShowDialog() == DialogResult.OK)
            {
                ex.src = Cv.LoadImage(op.FileName);
                pictureBox1.Image = ex.src.ToBitmap();
                imageOpened = true;

            }

        }

        private void extractFacesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (imageOpened) 
            {
                int n = ex.Detect();
                if (n > 0)
                {
                    MessageBox.Show(n.ToString() + " faces Extracted");
                    pictureBox1.Image = ex[0].ToBitmap();
                    numericUpDown1.Value = 0;
                    numericUpDown1.Maximum = n - 1;
                    numericUpDown1.Minimum = 0;
                    numericUpDown1.Enabled = true;
                    facesExtracted = true;
                }
            
            }
        }

        private void saveFaceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (facesExtracted)
            {
                SaveFileDialog sv = new SaveFileDialog();
                sv.FileName = "*.jpg";
                if (sv.ShowDialog() == DialogResult.OK)
                {
                    ex[(int)numericUpDown1.Value].SaveImage(sv.FileName);
                    listBox1.Items.Add(sv.FileName);
                    listBox1.Items.Add(ft.ToString());


                }
            }

        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (facesExtracted == false) return;            
            Point p=new Point();
            switch (comboBox1.SelectedIndex)
            {
                case 0: p=ft.LeftEye;
                    break;
                case 1: p = ft.RightEye;
                    break;
                case 2: p = ft.Nose;
                    break;
                case 3: p = ft.Mouth;
                    break;

            }
            textBox2.Text = p.ToString();
            
        }

        private void loadFeatureListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog op = new OpenFileDialog();
            op.Filter = "Feature List Files (*.lst)|*.lst";
            if (op.ShowDialog() == DialogResult.OK)
            {
                listBox1.Items.Clear();
                string buf;
                StreamReader dosya = File.OpenText(op.FileName);
                while ((buf = dosya.ReadLine()) != null)
                    listBox1.Items.Add(buf);
                dosya.Close();

            }
            
        }

        private void saveFeatureListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sv = new SaveFileDialog();
            sv.FileName = "*.lst";
            if (sv.ShowDialog() == DialogResult.OK)
            {
                StreamWriter dosya = File.CreateText(sv.FileName);
                foreach (string buf in listBox1.Items)
                    dosya.WriteLine(buf);
                dosya.Close();


            }

        }

        private void aboutToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            AboutBox1 a = new AboutBox1();
            a.ShowDialog();
        }
    
    }
}
