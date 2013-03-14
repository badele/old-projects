using System;
using System.IO;
using System.Collections;


namespace WindowsApplication1
{

	public delegate void FileEventHandler( FileInfo AInfo );
	public delegate void DirectoryEventHandler( DirectoryInfo AInfo );

	
	/// <summary>
	/// Description résumée de FieSpider.
	/// </summary>
	public class FieSpider
	{
		private bool _stoped = false;
		private string _directory;
		private string[] _toindex;

		public event FileEventHandler OnFile;
		public event DirectoryEventHandler OnDirectory;
		
		public FieSpider(string ADirectory,string AIgnore)
		{
			_directory = ADirectory;
			_toindex = AIgnore.ToUpper().Split(';');
		}

		public void scandir()
		{
			database.clearDocument();
			this.scandir(_directory);
		}
		

		public void scandir(string ADirectory)
		{
			string[] directorys = Directory.GetDirectories(ADirectory);
			string[] files = Directory.GetFiles(ADirectory);			
			
			// recherche des directorys
			IEnumerator  dirEnumerator = directorys.GetEnumerator();
			while ( !_stoped && dirEnumerator.MoveNext() ) 
			{
				this.scandir((string)dirEnumerator.Current);
			}

			// Recherche des fichiers dans le repertoire
			IEnumerator fileEnumerator = files.GetEnumerator();
			while ( !_stoped && fileEnumerator.MoveNext() ) 
			{
				FileInfo fileinfo = new FileInfo((string)fileEnumerator.Current);
				OnFile(fileinfo);
				
				//bool ignoreindex = Array.IndexOf(_toindex,fileinfo.Extension.ToUpper())==-1;
				
				int docId = database.addFile(fileinfo);
				Indexer indexer = new Indexer(@" \-_.~",3);
				indexer.ParseText(fileinfo.FullName);

				IDictionaryEnumerator myEnumerator = indexer.keywords.GetEnumerator();
				while ( myEnumerator.MoveNext() ) 
				{
					database.addDocumentKeyword(docId,myEnumerator.Key.ToString(),Convert.ToInt32(myEnumerator.Value.ToString()));
				}

			}

			if ( _stoped ) return;

			DirectoryInfo dirinfo = new DirectoryInfo(ADirectory);
			OnDirectory(dirinfo);
			database.addDirectory(dirinfo);
		}

		public void Stop()
		{
			_stoped = true;
		}

	}
}
