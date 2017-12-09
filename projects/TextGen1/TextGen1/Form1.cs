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

        TextGenerator t;
        public Form1()
        {
            InitializeComponent();
            t = new TextGenerator();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            richTextBox1.Clear();
            listBox1.Items.Clear();
            string len =t.GenerateText();
            string []lines = new string[1];
            lines[0] = len;
            richTextBox1.Lines=lines;
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
//            TextGenerator = new System.Collections.Hashtable();

//            TextGenerator.Add(
            TextGenerator t = new TextGenerator();


            
        }

        private void button2_Click(object sender, EventArgs e)
        {

            listBox1.Items.Clear();
            foreach (KeyValuePair<string, double> p in t.mList)
            {
                string s;
                s = p.Key + " " + p.Value.ToString();
                listBox1.Items.Add(s);

            }

        }

        private void button3_Click(object sender, EventArgs e)
        {
//            if(t == null)               t = new TextGenerator();
            t.Parse(richTextBox1.Lines);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            t.SaveData();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            t.LoadData();
            button5.Enabled = false;
            button1.Enabled = true;
            button2.Enabled = true;
            button3.Enabled = true;
            button4.Enabled = true;
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://derindelimavi.blogspot.com/");

        }
    }
}
