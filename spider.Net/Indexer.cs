using System;
using System.IO;
using System.Collections;

namespace WindowsApplication1
{
	/// <summary>
	/// Description résumée de Indexer.
	/// </summary>
	public class Indexer
	{
		private int _minlength;
		private string _delimiter;
		private char[] _delimiters;
		public readonly Hashtable keywords;
		
		public Indexer(string ADelimiter,int AMinLength)
		{
			keywords = new Hashtable();

			_minlength = AMinLength;
			_delimiter = ADelimiter;
			_delimiters = _delimiter.ToCharArray();
		}

		public void Save(int ADocId)
		{
			database.clearKeyword(ADocId);
			IDictionaryEnumerator myEnumerator = keywords.GetEnumerator();
			while ( myEnumerator.MoveNext() ) 
			{
				database.addKeyword(ADocId,myEnumerator.Key.ToString(),Convert.ToInt32(myEnumerator.Value.ToString()));
			}
		}

		public void ParseText(string AText)
		{
			TextReader tr = new StringReader(AText);
			this.ParseStream(tr);
		}


		public void ParseFile(string AFileName)
		{
			StreamReader sr = new StreamReader(AFileName);
			this.ParseStream(sr);
		}

		public void ParseStream(TextReader AStream)
		{
			String line;

			line = AStream.ToString();
			while ((line = AStream.ReadLine()) != null) 
			{
				this.ParseLine(line);
			}
		}

		private void ParseLine(string ALine)
		{
			// Parcour les mots clef
			string[] mots = ALine.Split(_delimiters);
			foreach (string mot in mots) 
			{
				if (mot.Length>=_minlength) 
				{
					if (keywords[mot] == null) 
					{
						keywords[mot] = 1;
					} 
					else 
					{
						keywords[mot] = (int)keywords[mot]+1;
					}
				}
			}
		}
	}
}
