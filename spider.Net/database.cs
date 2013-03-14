using System;
using System.Data.SqlClient;
using System.Data;
using System.IO;
using System.Collections;

namespace WindowsApplication1
{
	/// <summary>
	/// Description résumée de database.
	/// </summary>
	public class Document 
	{
		public int Id = -1;
		public string Type,Nom,Hash,Etat;
		public DateTime DateModification;
		public Int64 Taille;

		public Document() {}
		
		public Document(int id, string type,string nom,DateTime date,Int64 taille,string hash,string etat) 
		{
			Id = id;
			Type = type;
			Nom = nom;
			DateModification = date;
			Taille = taille;
			Hash = hash;
			Etat = etat;
		}
	}

	public class Clef 
	{
		public int Id=-1;
		public int DocumentId,Occurence;
		public string Mot;

		public Clef() {}
		
		public Clef(int id, int documentid,string mot,int occurence) 
		{
			Id = id;
			DocumentId = documentid;
			Mot = mot;
			Occurence = occurence;
		}
	}

	
	public class database
	{
		private static string connecstring = "Integrated Security=SSPI;Packet Size=4096;Data Source=\"SIN-5FBAB4\";Initial Catalog=searchengine;Persist Security Info=False;Workstation ID=\"SIN-5FBAB4\";";
		public  static TimeSpan elapsed;
		private static TimeSpan timestart;
		private static TimeSpan timeend;

		public database()
		{
		}


		public static SqlDataReader ReaderMesureTime(ref SqlCommand ACommand)
		{
			SqlDataReader dr;
			timestart = DateTime.Now.TimeOfDay;
			dr = ACommand.ExecuteReader();
			timeend = DateTime.Now.TimeOfDay;
			elapsed = timeend - timestart;

			return dr;
		}



		private static void readerToDocument(ref SqlDataReader AReader,ref Document ADoc)
		{
			ADoc.Id = Convert.ToInt32(AReader["DocumentId"].ToString());
			ADoc.Type = AReader["Type"].ToString();
			ADoc.Nom = AReader["Nom"].ToString();
			ADoc.DateModification = Convert.ToDateTime(AReader["DateModification"].ToString());
			ADoc.Taille = Convert.ToInt64(AReader["Taille"].ToString());
			ADoc.Hash = AReader["Hash"].ToString();
			ADoc.Etat = AReader["Etat"].ToString();
		}

		public static Document[] searchDocument(string AClauseWhere,int limit)
		{
			string top = "";

			if (limit>0) 
			{
				top = "top " + limit.ToString();
			}
			
			string sql = "select " + top + " documents.* from documents inner join  documentclef on documents.documentid=documentclef.documentid where " + AClauseWhere;
			
			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			
			SqlCommand command = new SqlCommand(sql,connect);
			ArrayList list = new ArrayList();
			SqlDataReader dr = database.ReaderMesureTime(ref command);
			try 
			{
				while (dr.Read()) 
				{
					Document doc = new Document();
					readerToDocument(ref dr,ref doc);
					list.Add(doc);
				}
			}
			finally 
			{
				if (dr != null) dr.Close();
				command.Dispose();
				connect.Close();
			}

			return (Document[])list.ToArray(typeof(Document));
		}

		public static int addFile(FileInfo AInfo)
		{
			Document doc = new Document(-1,"Fichier",AInfo.FullName,AInfo.LastWriteTime,AInfo.Length,"MD5","Nouveau");
			return database.addFileInfo(ref doc);
		}

		public static void addDirectory(DirectoryInfo AInfo)
		{
			Document doc = new Document(-1,"Repertoire",AInfo.FullName,AInfo.LastWriteTime,0,"","Ok");
			database.addFileInfo(ref doc);
		}

		public static void addKeyword(int ADocId,string AKeyword,int AOccurence)
		{
			Clef clef = new Clef(-1,ADocId,AKeyword,AOccurence);
			database.addKeywordInfo(ref clef);
		}

		public static void addDocumentKeyword(int ADocId,string AKeyword,int AOccurence)
		{
			Clef clef = new Clef(-1,ADocId,AKeyword,AOccurence);
			database.addDocumentKeywordInfo(ref clef);
		}


		public static void clearDocument()
		{
			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			SqlCommand command = new SqlCommand("delete from documents",connect);
			command.ExecuteNonQuery();
			//command = new SqlCommand("delete from Clefs",connect);
			//command.ExecuteNonQuery();
			connect.Close();
		}

		public static void clearKeyword(int ADocId)
		{
			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			SqlCommand command = new SqlCommand("delete from Clefs where ClefID=@id",connect);
			command.Parameters.Add("@id",SqlDbType.Int).Value  = ADocId;
			command.ExecuteNonQuery();
			connect.Close();
		}

		public static Document GetNextIndex()
		{
			Document doc = new Document();

			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			SqlCommand command = new SqlCommand("select top 1 * from documents where type='fichier' and etat<>'OK' and etat<>'Erreur' and etat<>'FullText'",connect);
			SqlDataReader dr = command.ExecuteReader();
			if (dr.Read()) 
			{
				database.readerToDocument(ref dr,ref doc);
			}
			connect.Close();

			return doc;
		}


		private static int addFileInfo(ref Document ADoc)
		{
			int id=-1;

			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			SqlCommand command = new SqlCommand("insert into Documents (Type,Nom,DateModification,Taille,Hash,Etat) values (@type,@file,@date,@taille,@hash,@etat) select @@identity as id",connect);
			command.Parameters.Add("@type",SqlDbType.VarChar).Value  = ADoc.Type;
			command.Parameters.Add("@file",SqlDbType.VarChar).Value  = ADoc.Nom;
			command.Parameters.Add("@date",SqlDbType.DateTime).Value  = ADoc.DateModification;
			command.Parameters.Add("@taille",SqlDbType.Int).Value  = ADoc.Taille;
			command.Parameters.Add("@hash",SqlDbType.VarChar).Value = "md5";
			command.Parameters.Add("@etat",SqlDbType.VarChar).Value = ADoc.Etat;
			SqlDataReader dr = command.ExecuteReader();
			dr.Read();
			id = Convert.ToInt32(dr["id"].ToString());
			connect.Close();

			return id;
		}

		public static void updateFileInfo(ref Document ADoc)
		{
			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			SqlCommand command = new SqlCommand("update Documents set Type=@type,Nom=@file,DateModification=@date,Taille=@taille,Hash=@hash,Etat=@etat where DocumentId=@id",connect);
			command.Parameters.Add("@id",SqlDbType.VarChar).Value  = ADoc.Id;
			command.Parameters.Add("@type",SqlDbType.VarChar).Value  = ADoc.Type;
			command.Parameters.Add("@file",SqlDbType.VarChar).Value  = ADoc.Nom;
			command.Parameters.Add("@date",SqlDbType.DateTime).Value  = ADoc.DateModification;
			command.Parameters.Add("@taille",SqlDbType.Int).Value  = ADoc.Taille;
			command.Parameters.Add("@hash",SqlDbType.VarChar).Value = "md5";
			command.Parameters.Add("@etat",SqlDbType.VarChar).Value = ADoc.Etat;
			command.ExecuteNonQuery();
			connect.Close();
		}

		private static void addDocumentKeywordInfo(ref Clef AClef)
		{
			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			SqlCommand command = new SqlCommand("insert into Documentclef (DocumentId,Mot,Occurence) values (@docid,@mot,@occurence)",connect);
			command.Parameters.Add("@docid",SqlDbType.Int).Value  = AClef.DocumentId;
			command.Parameters.Add("@mot",SqlDbType.VarChar).Value  = AClef.Mot;
			command.Parameters.Add("@occurence",SqlDbType.Int).Value  = AClef.Occurence;
			command.ExecuteNonQuery();
			connect.Close();
		}


		private static void addKeywordInfo(ref Clef AClef)
		{
			SqlConnection connect = new SqlConnection(connecstring);
			connect.Open();
			SqlCommand command = new SqlCommand("insert into Clefs (DocumentId,Mot,Occurence) values (@docid,@mot,@occurence)",connect);
			command.Parameters.Add("@docid",SqlDbType.Int).Value  = AClef.DocumentId;
			command.Parameters.Add("@mot",SqlDbType.VarChar).Value  = AClef.Mot;
			command.Parameters.Add("@occurence",SqlDbType.Int).Value  = AClef.Occurence;
			command.ExecuteNonQuery();
			connect.Close();
		}



	}
}
