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
    public partial class KalibrationDlg : Form
    {
        public KalibrationDlg()
        {
            InitializeComponent();
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            int s;
            try
            {
                s = Convert.ToInt32(LengthAtReal.Text);
                if (s <= 0)
                {
                    MessageBox.Show("Gerçek uzunluğu boş geçemezsiniz ");
                    this.DialogResult = DialogResult.Cancel;

                }
                
            }
            catch 
            {
                MessageBox.Show("Gerçek uzunluğu boş geçemezsiniz ");
                this.DialogResult = DialogResult.Cancel;
                s = -1;
            }
            
            
            

        }
    }
}
