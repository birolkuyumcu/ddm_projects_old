using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WindowsFormsApplication1
{
    public class MultiMap<V>
    {
        // 1
        Dictionary<string, List<V>> _dictionary = new Dictionary<string, List<V>>();

        // 2
        public void Add(string key, V value)
        {
            List<V> list;
            if (this._dictionary.TryGetValue(key, out list))
            {
                // 2A.
                list.Add(value);
            }
            else
            {
                // 2B.
                list = new List<V>();
                list.Add(value);
                this._dictionary[key] = list;
            }
        }

        // 3
        public IEnumerable<string> Keys
        {
            get
            {
                return this._dictionary.Keys;
            }
        }

        // 4
        public List<V> this[string key]
        {
            get
            {
                List<V> list;
                if (this._dictionary.TryGetValue(key, out list))
                {
                    return list;
                }
                else
                {
                    return new List<V>();
                }
            }
        }


    }    
    
    
    class TextGenerator
    {
        public Dictionary<string, double> mList;
        public MultiMap<string> sList;
        int count;
        static Random rnd = new Random();
        public TextGenerator() 
        {
            mList = new Dictionary<string, double>();
            sList = new MultiMap<string>();
            count = 0;            
        }
        
        public void Parse(string [] lines)
        {
            char[] sep = { ' ' };
            foreach (string line in lines)
            {
//                string tline= line + " EndLine";
                
                string tline = line;
                string[] words = tline.Split(sep);
                for (int i = 0; i < words.Length - 1; i++)
                {
                    words[i].Trim();
                    words[i+1].Trim();
                    string Key = words[i] + " " + words[i + 1];
                    if (!mList.ContainsKey(Key))
                    {
                        mList.Add(Key, 1);
                        sList.Add(words[i], words[i + 1]);
                        count++;
                    }
                    else 
                    {
                        mList[Key] += 1.0;
                    }

                }

           }

        
        }
        public void SaveData()
        {
            FileStream dosya = new FileStream("Data.vri", FileMode.Create);
            BinaryWriter tw = new BinaryWriter(dosya);
            foreach (string k in sList.Keys)
            {
                foreach (string v in sList[k])
                {
//                    dosya.WriteLine(k + "=" + v);
                    tw.Write(k);
                    tw.Write(v);
                    tw.Write(mList[k + " " + v]);
                }
            }
            tw.Close();
            dosya.Close();

        
        }
        public void LoadData()
        {
            FileStream dosya = new FileStream("Data.vri", FileMode.Open);
            BinaryReader tw = new BinaryReader(dosya);          
            
            string word1;
            string word2;
            double v;
            while(tw.BaseStream.Position < tw.BaseStream.Length ){
                word1 = tw.ReadString();
                word2 = tw.ReadString();
                v = tw.ReadDouble();
                mList.Add(word1 + " " + word2, v);
                sList.Add(word1, word2);
                count++;

            }
            tw.Close();
            dosya.Close();           
        
        
        }
        public string GenerateText()
        {
            string buf="";
            string s;

            IEnumerable<string> ls = sList.Keys;
            int selected = rnd.Next(ls.Count());
            
            buf=ls.ElementAt(selected);

            s = NextWord(buf);
            buf +=" "+s;
            while (s != null) 
            {

                s = NextWord(s);
                buf += " " + s;
                
            }

            return buf;       
                 
        }
        string NextWord(string word) 
        {
            List<string>nwords =sList[word];
            int total = 0;
            foreach (string nword in nwords) {
                string Key = word + " " + nword;
                total += ( int ) mList[Key];
            }
            if (total == 0) return null;
            int selected = rnd.Next(total+1);
            foreach (string nword in nwords)
            {
                string Key = word + " " + nword;
                selected -= (int) mList[Key];
                if (selected <= 0) return nword;
            }

            return null;
         
        }
        
    }
}
