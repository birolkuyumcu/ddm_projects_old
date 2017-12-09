using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Cetvel
{
    public partial class mesResultDlg : Form
    {
        public mesResultDlg(Point p1,Point p2, double iresult)
        {
            InitializeComponent();
            point1XY.Text = p1.ToString();
            point2XY.Text = p2.ToString();
            result.Text = String.Format("{0:F1}", iresult);
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
