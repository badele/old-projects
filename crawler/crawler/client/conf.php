<?php
/*
 * Created on 24 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
  
 $database="crawler";
 $mysql_user = "crawler";
 $mysql_password = "crawler"; 
 $mysql_host = "localhost";

 
 
 
 $debug_db=0;
 
 $autoincrement = 0;
 
 // Lines
 //$nb_iteration = 51;
 $stat_interval = 60;
 $nb_bulk_page = 10; 
 
 
 
 $nb_bulk_lines = 100; 
 $show_elapsed_after = 0;
 $show_elapsed_message = 'queue';

 $wait_process = 1;
 $minimal_word_size = 3;
 $max_document_size=128*1024;
 $save_rootdir = '/home/b_adele/document/project/crawler/crawler/queues';
 $weight_word=1;
 $weight_meta_keyword=5;
 $weight_title=10;
 $weight_url=15;
 $weight_domain=20;
 
 $weight_intags=array(
		'em'=>2,
		'strong' => 3,
		'title' => 12,
		'h1' => 10,
		'h2' => 8,
		'h3' => 6,
		'h4' => 4,
		'h5' => 3,
		'h6' => 2,
		'dt' => 3,
		'mybody' => 1 
 );
 $weight_attribut=ARRAY();
?>
