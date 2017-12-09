using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AcuteInflammations
{
    public partial class Form1 : Form
    {
        IntPtr ann;

        public Form1()
        {
            InitializeComponent();            
            ann = Fann.IO.create_from_file("Acute_Inflammations1.net");
            if (ann.ToInt32() == 0)
            {
                OpenFileDialog op = new OpenFileDialog();
                op.Title = "Select Neural Network File";
                op.FileName = "Acute_Inflammations1.net";
                if (op.ShowDialog() == DialogResult.OK)
                {
                    ann = Fann.IO.create_from_file("Acute_Inflammations1.net");
                }
                else
                    Application.Exit();
            }

        }

        private void maskedTextBox1_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            groupBox2.Enabled = false;
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            groupBox2.Enabled = false;
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            groupBox2.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            float[] inputs = new float[6];
            float temp;
            temp = float.Parse(maskedTextBox1.Text);
            inputs[0] = (temp - (float)35.0) / ((float)42.0 - (float)35.0);
            
            if (checkBox1.Checked)
                inputs[1] = 1;
            else
                inputs[1] = 0;

            if (checkBox2.Checked)
                inputs[2] = 1;
            else
                inputs[2] = 0;

            if (checkBox3.Checked)
                inputs[3] = 1;
            else
                inputs[3] = 0;

            if (checkBox4.Checked)
                inputs[4] = 1;
            else
                inputs[4] = 0;

            if (checkBox5.Checked)
                inputs[5] = 1;
            else
                inputs[5] = 0;

            groupBox2.Enabled = true;

            float[] outputs = Fann.run(ann, inputs);

            if (outputs[0] > 0.5)
                checkBox6.Checked = true;
            else
                checkBox6.Checked = false;

            if (outputs[1] > 0.5)
                checkBox7.Checked = true;
            else
                checkBox7.Checked = false;

            textBox1.Text = outputs[0].ToString();
            textBox2.Text = outputs[1].ToString();           

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            groupBox2.Enabled = false;
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            groupBox2.Enabled = false;
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://derindelimavi.blogspot.com/2010/04/yapay-zeka-tbbn-hizmetinde-4-acute.html");
        }
    }
}
