using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;

using SteepValley.Windows.Forms;
using SteepValley.Windows.Forms.ThemedControls;

using System.Runtime.InteropServices;

using System.Diagnostics;

//faire la recherche par timer automatique et ajouter l'option
//Avant d'utiliser le soundex regarer la taille avant et apres

namespace WindowsApplication1
{
	/// <summary>
	/// Description résumée de Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.StatusBar statusBar1;
		private System.ComponentModel.IContainer components;
		private int dircount= 0;
		private int filecount = 0;
		private FieSpider spider;
		private System.Windows.Forms.TabControl tbIndex;
		private System.Windows.Forms.TabPage tpIndexation;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.TabPage tpConfig;
		private System.Windows.Forms.TextBox tbxToIndex;
		private System.Windows.Forms.MainMenu mainMenu1;
		private System.Windows.Forms.ToolBar toolBar1;
		internal SteepValley.Windows.Forms.XPCaptionPane xpCaptionPane2;
		internal SteepValley.Windows.Forms.ThemedControls.XPTaskBoxSpecial XpTaskBoxSpecial1;
		private System.Windows.Forms.Button btnSearch;
		private System.Windows.Forms.TextBox tbxSearch;
		private SteepValley.Windows.Forms.XPCaptionPane xpCaptionPane1;
		private SteepValley.Windows.Forms.XPListView xpListView1;
		private bool _stop =false;
		private System.Windows.Forms.ImageList imlSmall;
		private System.Windows.Forms.ImageList imlLarge;
		private SHFILEINFO shinfo = new SHFILEINFO();
		private SteepValley.Windows.Forms.ThemedControls.XPTaskBox xpTaskBox1;
		private SteepValley.Windows.Forms.XPLinkedLabelIcon xpLinkedLabelIcon1;
		private SteepValley.Windows.Forms.XPLinkedLabelIcon xpLinkedLabelIcon2;
		private SteepValley.Windows.Forms.XPLinkedLabelIcon xpLinkedLabelIcon3;
		private SteepValley.Windows.Forms.XPLinkedLabelIcon xpLinkedLabelIcon4;
		private SteepValley.Windows.Forms.XPLinkedLabelIcon xpLinkedLabelIcon5;
		private Hashtable _extentions = new Hashtable();
		private System.Windows.Forms.CheckBox cbxLimit;
		private TimeSpan timeelapsed;
		private System.Windows.Forms.MenuItem menuItem5;
		private System.Windows.Forms.ContextMenu pmTrie;
		private System.Windows.Forms.Button btnTrie;
		private System.Windows.Forms.MenuItem menuDossier;
		private System.Windows.Forms.MenuItem menuFichier;
		private System.Windows.Forms.MenuItem menuDate;
		private System.Windows.Forms.MenuItem menuTaile;
		private System.Windows.Forms.MenuItem menuGroupe;
		private System.Windows.Forms.ColumnHeader cmFichier;
		private System.Windows.Forms.ColumnHeader cmDirectory;
		private System.Windows.Forms.ColumnHeader cmExtension;
		private int _limit = 500;

		public Form1()
		{
			//
			// Requis pour la prise en charge du Concepteur Windows Forms
			//
			InitializeComponent();

			//
			// TODO : ajoutez le code du constructeur après l'appel à InitializeComponent
			//
		}

		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Code généré par le Concepteur Windows Form
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Form1));
			this.statusBar1 = new System.Windows.Forms.StatusBar();
			this.tbIndex = new System.Windows.Forms.TabControl();
			this.tpIndexation = new System.Windows.Forms.TabPage();
			this.button4 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.button1 = new System.Windows.Forms.Button();
			this.tpConfig = new System.Windows.Forms.TabPage();
			this.tbxToIndex = new System.Windows.Forms.TextBox();
			this.mainMenu1 = new System.Windows.Forms.MainMenu();
			this.toolBar1 = new System.Windows.Forms.ToolBar();
			this.xpCaptionPane2 = new SteepValley.Windows.Forms.XPCaptionPane();
			this.xpTaskBox1 = new SteepValley.Windows.Forms.ThemedControls.XPTaskBox();
			this.xpLinkedLabelIcon5 = new SteepValley.Windows.Forms.XPLinkedLabelIcon();
			this.xpLinkedLabelIcon4 = new SteepValley.Windows.Forms.XPLinkedLabelIcon();
			this.xpLinkedLabelIcon3 = new SteepValley.Windows.Forms.XPLinkedLabelIcon();
			this.xpLinkedLabelIcon2 = new SteepValley.Windows.Forms.XPLinkedLabelIcon();
			this.xpLinkedLabelIcon1 = new SteepValley.Windows.Forms.XPLinkedLabelIcon();
			this.XpTaskBoxSpecial1 = new SteepValley.Windows.Forms.ThemedControls.XPTaskBoxSpecial();
			this.cbxLimit = new System.Windows.Forms.CheckBox();
			this.btnSearch = new System.Windows.Forms.Button();
			this.tbxSearch = new System.Windows.Forms.TextBox();
			this.xpCaptionPane1 = new SteepValley.Windows.Forms.XPCaptionPane();
			this.btnTrie = new System.Windows.Forms.Button();
			this.pmTrie = new System.Windows.Forms.ContextMenu();
			this.menuDossier = new System.Windows.Forms.MenuItem();
			this.menuFichier = new System.Windows.Forms.MenuItem();
			this.menuDate = new System.Windows.Forms.MenuItem();
			this.menuTaile = new System.Windows.Forms.MenuItem();
			this.menuItem5 = new System.Windows.Forms.MenuItem();
			this.menuGroupe = new System.Windows.Forms.MenuItem();
			this.xpListView1 = new SteepValley.Windows.Forms.XPListView(this.components);
			this.cmFichier = new System.Windows.Forms.ColumnHeader();
			this.cmDirectory = new System.Windows.Forms.ColumnHeader();
			this.cmExtension = new System.Windows.Forms.ColumnHeader();
			this.imlLarge = new System.Windows.Forms.ImageList(this.components);
			this.imlSmall = new System.Windows.Forms.ImageList(this.components);
			this.tbIndex.SuspendLayout();
			this.tpIndexation.SuspendLayout();
			this.tpConfig.SuspendLayout();
			this.xpCaptionPane2.SuspendLayout();
			this.xpTaskBox1.SuspendLayout();
			this.XpTaskBoxSpecial1.SuspendLayout();
			this.xpCaptionPane1.SuspendLayout();
			this.SuspendLayout();
			// 
			// statusBar1
			// 
			this.statusBar1.Location = new System.Drawing.Point(0, 472);
			this.statusBar1.Name = "statusBar1";
			this.statusBar1.Size = new System.Drawing.Size(560, 22);
			this.statusBar1.TabIndex = 4;
			// 
			// tbIndex
			// 
			this.tbIndex.Controls.Add(this.tpIndexation);
			this.tbIndex.Controls.Add(this.tpConfig);
			this.tbIndex.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.tbIndex.Location = new System.Drawing.Point(0, 376);
			this.tbIndex.Name = "tbIndex";
			this.tbIndex.SelectedIndex = 0;
			this.tbIndex.Size = new System.Drawing.Size(560, 96);
			this.tbIndex.TabIndex = 8;
			// 
			// tpIndexation
			// 
			this.tpIndexation.Controls.Add(this.button4);
			this.tpIndexation.Controls.Add(this.button3);
			this.tpIndexation.Controls.Add(this.button2);
			this.tpIndexation.Controls.Add(this.button1);
			this.tpIndexation.Location = new System.Drawing.Point(4, 22);
			this.tpIndexation.Name = "tpIndexation";
			this.tpIndexation.Size = new System.Drawing.Size(552, 70);
			this.tpIndexation.TabIndex = 0;
			this.tpIndexation.Text = "Index";
			// 
			// button4
			// 
			this.button4.Location = new System.Drawing.Point(144, 40);
			this.button4.Name = "button4";
			this.button4.Size = new System.Drawing.Size(96, 23);
			this.button4.TabIndex = 11;
			this.button4.Text = "Arreter le scan";
			this.button4.Click += new System.EventHandler(this.button4_Click);
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(144, 8);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(96, 23);
			this.button3.TabIndex = 10;
			this.button3.Text = "Arreter le scan";
			this.button3.Click += new System.EventHandler(this.button3_Click_1);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(8, 40);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(128, 23);
			this.button2.TabIndex = 9;
			this.button2.Text = "Indexer les doocuments";
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(8, 8);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(128, 23);
			this.button1.TabIndex = 8;
			this.button1.Text = "Indexer les repertoires";
			this.button1.Click += new System.EventHandler(this.button1_Click_1);
			// 
			// tpConfig
			// 
			this.tpConfig.Controls.Add(this.tbxToIndex);
			this.tpConfig.Location = new System.Drawing.Point(4, 22);
			this.tpConfig.Name = "tpConfig";
			this.tpConfig.Size = new System.Drawing.Size(552, 70);
			this.tpConfig.TabIndex = 1;
			this.tpConfig.Text = "Config";
			// 
			// tbxToIndex
			// 
			this.tbxToIndex.Location = new System.Drawing.Point(8, 8);
			this.tbxToIndex.Name = "tbxToIndex";
			this.tbxToIndex.Size = new System.Drawing.Size(192, 20);
			this.tbxToIndex.TabIndex = 7;
			this.tbxToIndex.Text = ".txt;.cs;.html;.aspx;.ascx;.asmx;.pov;.ini";
			// 
			// toolBar1
			// 
			this.toolBar1.Appearance = System.Windows.Forms.ToolBarAppearance.Flat;
			this.toolBar1.DropDownArrows = true;
			this.toolBar1.Location = new System.Drawing.Point(0, 0);
			this.toolBar1.Name = "toolBar1";
			this.toolBar1.ShowToolTips = true;
			this.toolBar1.Size = new System.Drawing.Size(560, 42);
			this.toolBar1.TabIndex = 11;
			// 
			// xpCaptionPane2
			// 
			this.xpCaptionPane2.BackColor = System.Drawing.SystemColors.AppWorkspace;
			// 
			// xpCaptionPane2.CaptionControl
			// 
			this.xpCaptionPane2.CaptionControl.Dock = System.Windows.Forms.DockStyle.Top;
			this.xpCaptionPane2.CaptionControl.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Bold);
			this.xpCaptionPane2.CaptionControl.Location = new System.Drawing.Point(1, 1);
			this.xpCaptionPane2.CaptionControl.Name = "caption";
			this.xpCaptionPane2.CaptionControl.Size = new System.Drawing.Size(206, 20);
			this.xpCaptionPane2.CaptionControl.TabIndex = 0;
			this.xpCaptionPane2.CaptionControl.Text = "Outils";
			this.xpCaptionPane2.CaptionText = "Outils";
			this.xpCaptionPane2.Controls.Add(this.xpTaskBox1);
			this.xpCaptionPane2.Controls.Add(this.XpTaskBoxSpecial1);
			this.xpCaptionPane2.Controls.Add(this.xpCaptionPane2.CaptionControl);
			this.xpCaptionPane2.Dock = System.Windows.Forms.DockStyle.Left;
			this.xpCaptionPane2.DockPadding.Bottom = 1;
			this.xpCaptionPane2.DockPadding.Left = 1;
			this.xpCaptionPane2.DockPadding.Right = 1;
			this.xpCaptionPane2.DockPadding.Top = 1;
			this.xpCaptionPane2.Location = new System.Drawing.Point(0, 42);
			this.xpCaptionPane2.Name = "xpCaptionPane2";
			this.xpCaptionPane2.Size = new System.Drawing.Size(208, 334);
			this.xpCaptionPane2.TabIndex = 13;
			// 
			// xpTaskBox1
			// 
			this.xpTaskBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.xpTaskBox1.BackColor = System.Drawing.Color.Transparent;
			this.xpTaskBox1.Controls.Add(this.xpLinkedLabelIcon5);
			this.xpTaskBox1.Controls.Add(this.xpLinkedLabelIcon4);
			this.xpTaskBox1.Controls.Add(this.xpLinkedLabelIcon3);
			this.xpTaskBox1.Controls.Add(this.xpLinkedLabelIcon2);
			this.xpTaskBox1.Controls.Add(this.xpLinkedLabelIcon1);
			this.xpTaskBox1.DockPadding.Bottom = 4;
			this.xpTaskBox1.DockPadding.Left = 4;
			this.xpTaskBox1.DockPadding.Right = 4;
			this.xpTaskBox1.DockPadding.Top = 44;
			this.xpTaskBox1.HeaderText = "Liste";
			this.xpTaskBox1.Icon = ((System.Drawing.Icon)(resources.GetObject("xpTaskBox1.Icon")));
			this.xpTaskBox1.Location = new System.Drawing.Point(4, 156);
			this.xpTaskBox1.Name = "xpTaskBox1";
			this.xpTaskBox1.Size = new System.Drawing.Size(200, 184);
			this.xpTaskBox1.TabIndex = 4;
			this.xpTaskBox1.ThemeFormat.BodyColor = System.Drawing.Color.FromArgb(((System.Byte)(197)), ((System.Byte)(210)), ((System.Byte)(240)));
			this.xpTaskBox1.ThemeFormat.BodyFont = new System.Drawing.Font("Tahoma", 8F);
			this.xpTaskBox1.ThemeFormat.BodyTextColor = System.Drawing.Color.FromArgb(((System.Byte)(33)), ((System.Byte)(93)), ((System.Byte)(198)));
			this.xpTaskBox1.ThemeFormat.BorderColor = System.Drawing.Color.White;
			this.xpTaskBox1.ThemeFormat.ChevronDown = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronDown")));
			this.xpTaskBox1.ThemeFormat.ChevronDownHighlight = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronDownHighlight")));
			this.xpTaskBox1.ThemeFormat.ChevronUp = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronUp")));
			this.xpTaskBox1.ThemeFormat.ChevronUpHighlight = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronUpHighlight")));
			this.xpTaskBox1.ThemeFormat.HeaderFont = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
			this.xpTaskBox1.ThemeFormat.HeaderTextColor = System.Drawing.Color.FromArgb(((System.Byte)(33)), ((System.Byte)(93)), ((System.Byte)(198)));
			this.xpTaskBox1.ThemeFormat.HeaderTextHighlightColor = System.Drawing.Color.FromArgb(((System.Byte)(66)), ((System.Byte)(142)), ((System.Byte)(255)));
			this.xpTaskBox1.ThemeFormat.LeftHeaderColor = System.Drawing.Color.White;
			this.xpTaskBox1.ThemeFormat.RightHeaderColor = System.Drawing.Color.FromArgb(((System.Byte)(197)), ((System.Byte)(210)), ((System.Byte)(240)));
			// 
			// xpLinkedLabelIcon5
			// 
			this.xpLinkedLabelIcon5.BackColor = System.Drawing.Color.Transparent;
			this.xpLinkedLabelIcon5.DisabledLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(42)), ((System.Byte)(42)), ((System.Byte)(42)));
			this.xpLinkedLabelIcon5.Icon = ((System.Drawing.Icon)(resources.GetObject("xpLinkedLabelIcon5.Icon")));
			this.xpLinkedLabelIcon5.LinkArea = new System.Windows.Forms.LinkArea(0, 5);
			this.xpLinkedLabelIcon5.LinkColor = System.Drawing.Color.FromArgb(((System.Byte)(0)), ((System.Byte)(0)), ((System.Byte)(255)));
			this.xpLinkedLabelIcon5.Location = new System.Drawing.Point(8, 112);
			this.xpLinkedLabelIcon5.Name = "xpLinkedLabelIcon5";
			this.xpLinkedLabelIcon5.Size = new System.Drawing.Size(60, 16);
			this.xpLinkedLabelIcon5.TabIndex = 4;
			this.xpLinkedLabelIcon5.Tag = "4";
			this.xpLinkedLabelIcon5.Text = "Détaillé";
			this.xpLinkedLabelIcon5.VisitedLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(128)), ((System.Byte)(0)), ((System.Byte)(128)));
			this.xpLinkedLabelIcon5.LinkClicked += new SteepValley.Windows.Forms.XPLinkedLabelIcon.LinkClickedEventHandler(this.xpLinkedLabelIcon1_LinkClicked);
			// 
			// xpLinkedLabelIcon4
			// 
			this.xpLinkedLabelIcon4.BackColor = System.Drawing.Color.Transparent;
			this.xpLinkedLabelIcon4.DisabledLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(42)), ((System.Byte)(42)), ((System.Byte)(42)));
			this.xpLinkedLabelIcon4.Icon = ((System.Drawing.Icon)(resources.GetObject("xpLinkedLabelIcon4.Icon")));
			this.xpLinkedLabelIcon4.LinkArea = new System.Windows.Forms.LinkArea(0, 5);
			this.xpLinkedLabelIcon4.LinkColor = System.Drawing.Color.FromArgb(((System.Byte)(0)), ((System.Byte)(0)), ((System.Byte)(255)));
			this.xpLinkedLabelIcon4.Location = new System.Drawing.Point(8, 96);
			this.xpLinkedLabelIcon4.Name = "xpLinkedLabelIcon4";
			this.xpLinkedLabelIcon4.Size = new System.Drawing.Size(46, 16);
			this.xpLinkedLabelIcon4.TabIndex = 3;
			this.xpLinkedLabelIcon4.Tag = "3";
			this.xpLinkedLabelIcon4.Text = "Liste";
			this.xpLinkedLabelIcon4.VisitedLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(128)), ((System.Byte)(0)), ((System.Byte)(128)));
			this.xpLinkedLabelIcon4.LinkClicked += new SteepValley.Windows.Forms.XPLinkedLabelIcon.LinkClickedEventHandler(this.xpLinkedLabelIcon1_LinkClicked);
			// 
			// xpLinkedLabelIcon3
			// 
			this.xpLinkedLabelIcon3.BackColor = System.Drawing.Color.Transparent;
			this.xpLinkedLabelIcon3.DisabledLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(42)), ((System.Byte)(42)), ((System.Byte)(42)));
			this.xpLinkedLabelIcon3.Icon = ((System.Drawing.Icon)(resources.GetObject("xpLinkedLabelIcon3.Icon")));
			this.xpLinkedLabelIcon3.LinkArea = new System.Windows.Forms.LinkArea(0, 5);
			this.xpLinkedLabelIcon3.LinkColor = System.Drawing.Color.FromArgb(((System.Byte)(0)), ((System.Byte)(0)), ((System.Byte)(255)));
			this.xpLinkedLabelIcon3.Location = new System.Drawing.Point(8, 80);
			this.xpLinkedLabelIcon3.Name = "xpLinkedLabelIcon3";
			this.xpLinkedLabelIcon3.Size = new System.Drawing.Size(45, 16);
			this.xpLinkedLabelIcon3.TabIndex = 2;
			this.xpLinkedLabelIcon3.Tag = "2";
			this.xpLinkedLabelIcon3.Text = "Petit";
			this.xpLinkedLabelIcon3.VisitedLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(128)), ((System.Byte)(0)), ((System.Byte)(128)));
			this.xpLinkedLabelIcon3.LinkClicked += new SteepValley.Windows.Forms.XPLinkedLabelIcon.LinkClickedEventHandler(this.xpLinkedLabelIcon1_LinkClicked);
			// 
			// xpLinkedLabelIcon2
			// 
			this.xpLinkedLabelIcon2.BackColor = System.Drawing.Color.Transparent;
			this.xpLinkedLabelIcon2.DisabledLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(42)), ((System.Byte)(42)), ((System.Byte)(42)));
			this.xpLinkedLabelIcon2.Icon = ((System.Drawing.Icon)(resources.GetObject("xpLinkedLabelIcon2.Icon")));
			this.xpLinkedLabelIcon2.LinkArea = new System.Windows.Forms.LinkArea(0, 5);
			this.xpLinkedLabelIcon2.LinkColor = System.Drawing.Color.FromArgb(((System.Byte)(0)), ((System.Byte)(0)), ((System.Byte)(255)));
			this.xpLinkedLabelIcon2.Location = new System.Drawing.Point(8, 64);
			this.xpLinkedLabelIcon2.Name = "xpLinkedLabelIcon2";
			this.xpLinkedLabelIcon2.Size = new System.Drawing.Size(51, 16);
			this.xpLinkedLabelIcon2.TabIndex = 1;
			this.xpLinkedLabelIcon2.Tag = "1";
			this.xpLinkedLabelIcon2.Text = "Large";
			this.xpLinkedLabelIcon2.VisitedLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(128)), ((System.Byte)(0)), ((System.Byte)(128)));
			this.xpLinkedLabelIcon2.LinkClicked += new SteepValley.Windows.Forms.XPLinkedLabelIcon.LinkClickedEventHandler(this.xpLinkedLabelIcon1_LinkClicked);
			// 
			// xpLinkedLabelIcon1
			// 
			this.xpLinkedLabelIcon1.BackColor = System.Drawing.Color.Transparent;
			this.xpLinkedLabelIcon1.DisabledLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(42)), ((System.Byte)(42)), ((System.Byte)(42)));
			this.xpLinkedLabelIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("xpLinkedLabelIcon1.Icon")));
			this.xpLinkedLabelIcon1.LinkArea = new System.Windows.Forms.LinkArea(0, 5);
			this.xpLinkedLabelIcon1.LinkColor = System.Drawing.Color.FromArgb(((System.Byte)(0)), ((System.Byte)(0)), ((System.Byte)(255)));
			this.xpLinkedLabelIcon1.Location = new System.Drawing.Point(8, 48);
			this.xpLinkedLabelIcon1.Name = "xpLinkedLabelIcon1";
			this.xpLinkedLabelIcon1.Size = new System.Drawing.Size(45, 16);
			this.xpLinkedLabelIcon1.TabIndex = 0;
			this.xpLinkedLabelIcon1.Tag = "0";
			this.xpLinkedLabelIcon1.Text = "Titre";
			this.xpLinkedLabelIcon1.VisitedLinkColor = System.Drawing.Color.FromArgb(((System.Byte)(128)), ((System.Byte)(0)), ((System.Byte)(128)));
			this.xpLinkedLabelIcon1.LinkClicked += new SteepValley.Windows.Forms.XPLinkedLabelIcon.LinkClickedEventHandler(this.xpLinkedLabelIcon1_LinkClicked);
			// 
			// XpTaskBoxSpecial1
			// 
			this.XpTaskBoxSpecial1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.XpTaskBoxSpecial1.BackColor = System.Drawing.Color.Transparent;
			this.XpTaskBoxSpecial1.Controls.Add(this.cbxLimit);
			this.XpTaskBoxSpecial1.Controls.Add(this.btnSearch);
			this.XpTaskBoxSpecial1.Controls.Add(this.tbxSearch);
			this.XpTaskBoxSpecial1.DockPadding.Bottom = 4;
			this.XpTaskBoxSpecial1.DockPadding.Left = 4;
			this.XpTaskBoxSpecial1.DockPadding.Right = 4;
			this.XpTaskBoxSpecial1.DockPadding.Top = 44;
			this.XpTaskBoxSpecial1.HeaderText = "Recherche";
			this.XpTaskBoxSpecial1.Icon = ((System.Drawing.Icon)(resources.GetObject("XpTaskBoxSpecial1.Icon")));
			this.XpTaskBoxSpecial1.Location = new System.Drawing.Point(4, 24);
			this.XpTaskBoxSpecial1.Name = "XpTaskBoxSpecial1";
			this.XpTaskBoxSpecial1.Size = new System.Drawing.Size(200, 128);
			this.XpTaskBoxSpecial1.TabIndex = 3;
			this.XpTaskBoxSpecial1.ThemeFormat.BodyColor = System.Drawing.Color.FromArgb(((System.Byte)(239)), ((System.Byte)(243)), ((System.Byte)(255)));
			this.XpTaskBoxSpecial1.ThemeFormat.BodyFont = new System.Drawing.Font("Tahoma", 8F);
			this.XpTaskBoxSpecial1.ThemeFormat.BodyTextColor = System.Drawing.Color.FromArgb(((System.Byte)(33)), ((System.Byte)(93)), ((System.Byte)(198)));
			this.XpTaskBoxSpecial1.ThemeFormat.BorderColor = System.Drawing.Color.White;
			this.XpTaskBoxSpecial1.ThemeFormat.ChevronDown = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronDown1")));
			this.XpTaskBoxSpecial1.ThemeFormat.ChevronDownHighlight = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronDownHighlight1")));
			this.XpTaskBoxSpecial1.ThemeFormat.ChevronUp = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronUp1")));
			this.XpTaskBoxSpecial1.ThemeFormat.ChevronUpHighlight = ((System.Drawing.Bitmap)(resources.GetObject("resource.ChevronUpHighlight1")));
			this.XpTaskBoxSpecial1.ThemeFormat.HeaderFont = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
			this.XpTaskBoxSpecial1.ThemeFormat.HeaderTextColor = System.Drawing.Color.White;
			this.XpTaskBoxSpecial1.ThemeFormat.HeaderTextHighlightColor = System.Drawing.Color.FromArgb(((System.Byte)(66)), ((System.Byte)(142)), ((System.Byte)(255)));
			this.XpTaskBoxSpecial1.ThemeFormat.LeftHeaderColor = System.Drawing.Color.FromArgb(((System.Byte)(1)), ((System.Byte)(72)), ((System.Byte)(178)));
			this.XpTaskBoxSpecial1.ThemeFormat.RightHeaderColor = System.Drawing.Color.FromArgb(((System.Byte)(40)), ((System.Byte)(91)), ((System.Byte)(197)));
			// 
			// cbxLimit
			// 
			this.cbxLimit.Checked = true;
			this.cbxLimit.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbxLimit.Location = new System.Drawing.Point(8, 93);
			this.cbxLimit.Name = "cbxLimit";
			this.cbxLimit.Size = new System.Drawing.Size(152, 24);
			this.cbxLimit.TabIndex = 14;
			this.cbxLimit.Text = "Limité la recherche à 500";
			this.cbxLimit.CheckedChanged += new System.EventHandler(this.cbxLimit_CheckedChanged);
			// 
			// btnSearch
			// 
			this.btnSearch.Location = new System.Drawing.Point(168, 64);
			this.btnSearch.Name = "btnSearch";
			this.btnSearch.Size = new System.Drawing.Size(24, 23);
			this.btnSearch.TabIndex = 13;
			this.btnSearch.Text = "...";
			this.btnSearch.Click += new System.EventHandler(this.btnSearch_Click_1);
			// 
			// tbxSearch
			// 
			this.tbxSearch.Location = new System.Drawing.Point(8, 64);
			this.tbxSearch.Name = "tbxSearch";
			this.tbxSearch.Size = new System.Drawing.Size(152, 20);
			this.tbxSearch.TabIndex = 12;
			this.tbxSearch.Text = "#document program";
			// 
			// xpCaptionPane1
			// 
			// 
			// xpCaptionPane1.CaptionControl
			// 
			this.xpCaptionPane1.CaptionControl.Dock = System.Windows.Forms.DockStyle.Top;
			this.xpCaptionPane1.CaptionControl.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Bold);
			this.xpCaptionPane1.CaptionControl.Location = new System.Drawing.Point(1, 1);
			this.xpCaptionPane1.CaptionControl.Name = "caption";
			this.xpCaptionPane1.CaptionControl.Size = new System.Drawing.Size(350, 20);
			this.xpCaptionPane1.CaptionControl.TabIndex = 0;
			this.xpCaptionPane1.CaptionControl.Text = "Fichiers";
			this.xpCaptionPane1.CaptionText = "Fichiers";
			this.xpCaptionPane1.Controls.Add(this.btnTrie);
			this.xpCaptionPane1.Controls.Add(this.xpCaptionPane1.CaptionControl);
			this.xpCaptionPane1.Controls.Add(this.xpListView1);
			this.xpCaptionPane1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.xpCaptionPane1.DockPadding.All = 1;
			this.xpCaptionPane1.Location = new System.Drawing.Point(208, 42);
			this.xpCaptionPane1.Name = "xpCaptionPane1";
			this.xpCaptionPane1.Size = new System.Drawing.Size(352, 334);
			this.xpCaptionPane1.TabIndex = 14;
			// 
			// btnTrie
			// 
			this.btnTrie.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.btnTrie.ContextMenu = this.pmTrie;
			this.btnTrie.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.btnTrie.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.btnTrie.Location = new System.Drawing.Point(256, 1);
			this.btnTrie.Name = "btnTrie";
			this.btnTrie.Size = new System.Drawing.Size(95, 20);
			this.btnTrie.TabIndex = 2;
			this.btnTrie.Text = "Trier par :";
			this.btnTrie.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.btnTrie.Click += new System.EventHandler(this.button5_Click);
			// 
			// pmTrie
			// 
			this.pmTrie.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																				   this.menuDossier,
																				   this.menuFichier,
																				   this.menuDate,
																				   this.menuTaile,
																				   this.menuItem5,
																				   this.menuGroupe});
			// 
			// menuDossier
			// 
			this.menuDossier.Index = 0;
			this.menuDossier.Text = "Dossier";
			this.menuDossier.Click += new System.EventHandler(this.menuItem1_Click);
			// 
			// menuFichier
			// 
			this.menuFichier.Index = 1;
			this.menuFichier.Text = "Type de fichier";
			this.menuFichier.Click += new System.EventHandler(this.menuItem1_Click);
			// 
			// menuDate
			// 
			this.menuDate.Index = 2;
			this.menuDate.Text = "Date";
			this.menuDate.Click += new System.EventHandler(this.menuItem1_Click);
			// 
			// menuTaile
			// 
			this.menuTaile.Index = 3;
			this.menuTaile.Text = "Taille";
			this.menuTaile.Click += new System.EventHandler(this.menuItem1_Click);
			// 
			// menuItem5
			// 
			this.menuItem5.Index = 4;
			this.menuItem5.Text = "-";
			// 
			// menuGroupe
			// 
			this.menuGroupe.Index = 5;
			this.menuGroupe.Text = "Grouper";
			// 
			// xpListView1
			// 
			this.xpListView1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.xpListView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
																						  this.cmFichier,
																						  this.cmDirectory,
																						  this.cmExtension});
			this.xpListView1.LargeImageList = this.imlLarge;
			this.xpListView1.Location = new System.Drawing.Point(0, 21);
			this.xpListView1.Name = "xpListView1";
			this.xpListView1.Size = new System.Drawing.Size(350, 312);
			this.xpListView1.SmallImageList = this.imlSmall;
			this.xpListView1.TabIndex = 1;
			this.xpListView1.TileColumns = new int[] {
														 1};
			this.xpListView1.View = SteepValley.Windows.Forms.ExtendedView.Details;
			this.xpListView1.DoubleClick += new System.EventHandler(this.xpListView1_DoubleClick);
			// 
			// cmFichier
			// 
			this.cmFichier.Text = "Fichier";
			this.cmFichier.Width = 290;
			// 
			// cmDirectory
			// 
			this.cmDirectory.Text = "Location";
			this.cmDirectory.Width = 390;
			// 
			// cmExtension
			// 
			this.cmExtension.Text = "Extension";
			this.cmExtension.Width = 80;
			// 
			// imlLarge
			// 
			this.imlLarge.ImageSize = new System.Drawing.Size(32, 32);
			this.imlLarge.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// imlSmall
			// 
			this.imlSmall.ImageSize = new System.Drawing.Size(16, 16);
			this.imlSmall.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// Form1
			// 
			this.AcceptButton = this.btnSearch;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(560, 494);
			this.Controls.Add(this.xpCaptionPane1);
			this.Controls.Add(this.xpCaptionPane2);
			this.Controls.Add(this.toolBar1);
			this.Controls.Add(this.tbIndex);
			this.Controls.Add(this.statusBar1);
			this.Menu = this.mainMenu1;
			this.Name = "Form1";
			this.Text = "Form1";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			this.tbIndex.ResumeLayout(false);
			this.tpIndexation.ResumeLayout(false);
			this.tpConfig.ResumeLayout(false);
			this.xpCaptionPane2.ResumeLayout(false);
			this.xpTaskBox1.ResumeLayout(false);
			this.XpTaskBoxSpecial1.ResumeLayout(false);
			this.xpCaptionPane1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// Point d'entrée principal de l'application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			// Contourne le bug des groupages
			Application.EnableVisualStyles();
			Application.DoEvents();
			Application.Run(new Form1());
		}

		public string ConvertQueryToSql(string AQuery)
		{
			/*
			 * select  documents.* from documents inner join  documentclef on documents.documentid=documentclef.documentid where 
				mot='outlook' and  documentclef.documentid in (select documentid from documentclef where mot='pst' and documentclef.documentid not in (select documentid from documentclef where mot='pas'  ))
			*/
			
			
			string word;
			string[] queries;
			string[] strings;
			int count;
			int i=0;
			string and_words = "";
			string or_words = "";
			string not_words = "";
			string sql_or = "";
			string sql_and = "";
			string sql_not = "";
			string clausewhere = "";
			

			// Parse les requetes
			i = 0;
			queries = AQuery.Split(' ');
			count = queries.Length;
			foreach (string query in queries) 
			{
				word = query.Trim();

				string boolean = word.Substring(0,1);
				switch (boolean) 
				{
					case "-":
						word = word.Replace(boolean,"");
						not_words += word + ";"; 
						break;
					case "#":
						word = word.Replace(boolean,"");
						or_words += word + ";";
						break;
					case "&":
						word = word.Replace(boolean,"");
						and_words += word + ";";
						break;
					default:
						and_words += word + ";";
						break;
				}
				i++;
			}

			// On ajoute égallement les et dans la clause or pour accéléré les recherches
			or_words += and_words;
			
			if (and_words.Length>0) and_words = and_words.Substring(0,and_words.Length-1);
			if (or_words.Length>0) or_words = or_words.Substring(0,or_words.Length-1);
			if (not_words.Length>0) not_words = not_words.Substring(0,not_words.Length-1);

			// On traite la clause ou
			i = 0;
			strings = or_words.Split(';');
			foreach (string keyword in strings) 
			{
				if (i>0) sql_or += " Or ";

				sql_or += "mot = '" + keyword + "'";

				i++;
			}

			// On traite la clause et
			if (and_words.Length>0) 
			{
				i = 0;
				strings = and_words.Split(';');
				foreach (string keyword in strings) 
				{
					if ((i==0 && or_words.Length>0) || i>0  ) sql_and += " And ";

					sql_and += "documents.documentid  in (select documentid from documentclef where mot = '" + keyword + "')";

					i++;
				}
			}

			// On traite la clause not
			if (not_words.Length>0)  
			{
				i = 0;
				strings = not_words.Split(';');
				foreach (string keyword in strings) 
				{
					if ((i==0 && or_words.Length>0 && and_words.Length>0) || i>0  ) sql_not += " And ";

					sql_not += "documents.documentid  not in (select documentid from documentclef where mot = '" + keyword + "')";

					i++;
				}
			}
			
			clausewhere = "(" + sql_or + ")";
			clausewhere += sql_and;
			clausewhere += sql_not;

			return clausewhere;

		}

		private void SearchFile()
		{
			IntPtr hImgSmall;
			IntPtr hImgLarge;
			Icon smallicon;
			Icon largeicon;
			XPListViewItem item;
			int imgidx = -1;

			statusBar1.Text = "Lancement de la recherche de '" + tbxSearch.Text + "' ..."; 

			// Efface tout les extenssions
			_extentions.Clear();
			
			// Efface les icones des images list
			imlSmall.Images.Clear();
			imlLarge.Images.Clear();
			
			// Initialise la vue
			xpListView1.BeginUpdate();
			xpListView1.Groups.Clear();
			xpListView1.Items.Clear();
			//xpListView1.Columns.Clear();
			/*xpListView1.Columns.Add("Fichier", 289, HorizontalAlignment.Left);
			xpListView1.Columns.Add("Location", 430, HorizontalAlignment.Left);
			xpListView1.Columns.Add("Extension", 120, HorizontalAlignment.Left);*/

			xpListView1.Sort();

			//timestart = DateTime.Now.TimeOfDay;
			Document[] docs = database.searchDocument(ConvertQueryToSql(tbxSearch.Text),_limit);
			timeelapsed = database.elapsed;
			//timeend = DateTime.Now.TimeOfDay;
			//timeelapsed = timeend - timestart;
			foreach (Document doc in docs) 
			{
				// On crée les icones
				if (_extentions[Path.GetExtension(doc.Nom)] == null )
				{
					// Corespondra à l'index
					_extentions[Path.GetExtension(doc.Nom)] = imlSmall.Images.Count;
					
					// Recupération du petit icone
					hImgSmall = Win32.SHGetFileInfo(doc.Nom, 0, ref shinfo,(uint)Marshal.SizeOf(shinfo),Win32.SHGFI_ICON |Win32.SHGFI_SMALLICON);
					smallicon = System.Drawing.Icon.FromHandle(shinfo.hIcon);
					imlSmall.Images.Add(smallicon);
					
					// recupération du grand icone
					hImgLarge = Win32.SHGetFileInfo(doc.Nom, 0,ref shinfo, (uint)Marshal.SizeOf(shinfo),Win32.SHGFI_ICON | Win32.SHGFI_LARGEICON);
					largeicon = System.Drawing.Icon.FromHandle(shinfo.hIcon);
					imlLarge.Images.Add(largeicon);
				} 
				imgidx = Convert.ToInt32(_extentions[Path.GetExtension(doc.Nom)].ToString());
				
				string infos = Path.GetFileName(doc.Nom) + ";" + Path.GetDirectoryName(doc.Nom) + ";" + Path.GetExtension(doc.Nom);
				item = new XPListViewItem(infos.Split(';'),imgidx);
				xpListView1.Items.Add(item);
			}

			xpListView1.EndUpdate();

			statusBar1.Text = "Recherche terminé de '" + tbxSearch.Text + "'"; 
		}

		public void DoRefresh()
		{
			// Compte le nombre de fichier trouvée
			string time = Math.Floor(timeelapsed.TotalMilliseconds).ToString();
			xpCaptionPane1.CaptionText = xpListView1.Items.Count.ToString() + " Fichier(s) en "+time + " ms";				
		}
		

		private void spider_OnDirectory(DirectoryInfo AInfo)
		{
			dircount++;
			statusBar1.Text = "("+dircount.ToString()+","+filecount.ToString()+") - Repertoire: " + AInfo.FullName;
			Application.DoEvents();
		}

		private void spider_OnFile(FileInfo AInfo)
		{
			filecount++;
			statusBar1.Text = "("+dircount.ToString()+","+filecount.ToString()+") - Fichier: " + AInfo.FullName;
			Application.DoEvents();
		}


		private void button2_Click(object sender, System.EventArgs e)
		{
			
			Document doc = database.GetNextIndex();
			while (!_stop && doc.Id!=-1) 
			{
				statusBar1.Text = "Indexe le document" + doc.Nom;
				Application.DoEvents();

				try 
				{
					Indexer indexer = new Indexer(" ,.:'\"",3);
					indexer.ParseFile(doc.Nom);
					indexer.Save(doc.Id);

					doc.Etat="OK";
					database.updateFileInfo(ref doc);

				}
				catch (Exception E) 
				{
					doc.Etat="Erreur";
					database.updateFileInfo(ref doc);
				}
				
				doc = database.GetNextIndex();
			}
		}


		private void button1_Click_1(object sender, System.EventArgs e)
		{
			spider = new FieSpider(@"c:\",tbxToIndex.Text);
			spider.OnDirectory +=new DirectoryEventHandler(spider_OnDirectory);
			spider.OnFile +=new FileEventHandler(spider_OnFile);
			spider.scandir();
		
		}

		private void button3_Click_1(object sender, System.EventArgs e)
		{
			spider.Stop();
		}

		private void button4_Click(object sender, System.EventArgs e)
		{
			_stop = true;
		}


		private void btnSearch_Click_1(object sender, System.EventArgs e)
		{
			SearchFile();
			DoRefresh();
		}


		private void xpLinkedLabelIcon1_LinkClicked(object sender, System.EventArgs e)
		{
			/*xpListView1.ResetColumnStyle(0);
			xpListView1.TileColumns = new int[2] {1, 2};
            xpListView1.SetColumnStyle(0, new Font(xpListView1.Font, FontStyle.Bold), xpListView1.ForeColor, xpListView1.BackColor);
			xpListView1.View = ExtendedView.Tile;*/
			xpListView1.ResetColumnStyle(0);

			XPLinkedLabelIcon label = (XPLinkedLabelIcon)sender;
			switch ((string)label.Tag) 
			{
				case "0":
					xpListView1.ResetColumnStyle(0);
					xpListView1.TileColumns = new int[2] {1, 2};
					xpListView1.SetColumnStyle(0, new Font(xpListView1.Font, FontStyle.Bold), xpListView1.ForeColor, xpListView1.BackColor);
					xpListView1.View = ExtendedView.Tile;
					break;
				case "1":
					xpListView1.View = ExtendedView.LargeIcon;
					break;
				case "2":
					xpListView1.View = ExtendedView.SmallIcon;
					break;
				case "3":
					xpListView1.View = ExtendedView.List;
					break;
				case "4":
					xpListView1.View = ExtendedView.Details;
					break;
			}

			xpListView1.RedrawItems();
			this.ResumeLayout();

		}

		private void cbxLimit_CheckedChanged(object sender, System.EventArgs e)
		{
			if (cbxLimit.Checked == true)
			{
				_limit = 500; 
			} 
			else { 
				_limit = 0; 
			}
		}

		private void xpListView1_DoubleClick(object sender, System.EventArgs e)
		{
			System.Diagnostics.Process.Start(xpListView1.SelectedItems[0].SubItems[1].Text+"\\"+xpListView1.SelectedItems[0].SubItems[0].Text);
		}

		private void button5_Click(object sender, System.EventArgs e)
		{
			pmTrie.Show(xpCaptionPane1,new Point(btnTrie.Location.X,btnTrie.Location.Y+btnTrie.Size.Height));
		}

		private void menuItem1_Click(object sender, System.EventArgs e)
		{
			MenuItem menuitem = (MenuItem)sender;
			switch (menuitem.Index) 
			{
				case 0:
					xpListView1.AutoGroupByColumn(1);
					break;
				case 1:
					xpListView1.AutoGroupByColumn(2);
					break;
			}
		}


	}
}
