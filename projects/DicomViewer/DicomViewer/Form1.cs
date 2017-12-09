using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using itk;

namespace DicomViewer
{
    public partial class Form1 : Form
    {
        private DicomLoader dcm=new DicomLoader();
        public Form1()
        {
            InitializeComponent();            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Dicom file |*.dcm";
            if (openFileDialog1.ShowDialog() == DialogResult.OK) {
                if (dcm.OpenDicomFile(openFileDialog1.FileName))
                    textBox1.Text = openFileDialog1.FileName;
                    pictureBox1.Image = dcm.GetImage();
            
            }
        }
    }
}
