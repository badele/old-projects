<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */

class Queues
{
	private $queue_dir; 
	private $task;
	private $items = array();
	
	function __construct()
	{
		$this->queue_dir = $GLOBALS['save_rootdir'];
	}
	
	function Add($task,$md5_url,$object)
	{
		$taskid = $task.'_'.$md5_url;
		
		$this->items[$taskid]['task'] = $task;
		$this->items[$taskid]['md5_url'] = $md5_url;
		$this->items[$taskid]['object'] = $object;
	}
	
	function Items()
	{
		return $this->items;
	}
	
	
	function Delete($queuename,$taskid)
	{
		$dir = "$this->queue_dir/$queuename"; 
		unlink("$dir/$taskid");
		unset($this->items[$taskid]);
	}

	private function CreateQueueIfNoExist($queuename)
	{
		$dir = "$this->queue_dir/$queuename"; 
		if (!file_exists($dir)) {
			mkdir($dir);
		}
	}
	
	function Reset($queuename)
	{
		$queue_dir = "$this->queue_dir/$queuename";
	
		// Efface la queue
		if (file_exists($queue_dir)) {
			if ($dh = opendir($queue_dir)) {
		        while (($file = readdir($dh)) !== false) {
		            if ($file!='.' && $file!='..') {
		            	@unlink(("$queue_dir/$file"));
		            }
		        }
		        closedir($dh);
		    }
		}
	}
	
	function SaveAll($queuename)
	{
		$this->CreateQueueIfNoExist($queuename);
		
		// Ecriture de la queue
		$dir = "$this->queue_dir/$queuename"; 
		foreach ($this->items as $taskid => $item)
		{
			$task = $item['task'];
			$object =  $item['object'];
			
			file_put_contents("$dir/$taskid",serialize($object));
		}
	}
	
	function Save($queuename,$taskid,$object,$serialize=true)
	{
		$this->CreateQueueIfNoExist($queuename);

		$dir = "$this->queue_dir/$queuename"; 
		if ($serialize) {
			$object = serialize($object);
		}	
	
		file_put_contents("$dir/$taskid",$object);
	}
	
	function Load($queuename)
	{
		$this->items = array();
		 
		$dir = "$this->queue_dir/$queuename"; 
		if (file_exists($dir)) {
			if ($dh = opendir($dir)) {
		        while (($file = readdir($dh)) !== false) {
		            if ($file!='.' && $file!='..') {
		            	if (preg_match("#(.+)([0-9a-f]{32})#",$file,$match)) {
			            	$object = unserialize(file_get_contents("$dir/$file"));
			            	$this->items[$file]['task'] = $match[1]; 
			            	$this->items[$file]['md5_url'] = $object;
			            	$this->items[$file]['object'] = $object;
		            	}
		            }
		        }
		        closedir($dh);
		    }
		}
	}
	
	
	
	function ExecuteQueues($queuename)
	{
		foreach ($this->items as $taskid => $item)
		{
			$task = $item['task'];
			call_user_func(sprintf("%s_%s",$queuename,$task),$this,$taskid); 
		}
	}
}



function q_addToQueue($task,$pages)
{
	$queue_dir = $GLOBALS['save_rootdir']."/queue";

	// Ecriture de la queue
	foreach ($pages as $item => $page)
	{
		$md5_url = $page->md5_url;
		
		file_put_contents(sprintf("%s/%s_%s",$queue_dir,$task,$md5_url),serialize($page));
	}
	
}

function q_removePageFromQueue($md5_url)
{
	$queue_dir = $GLOBALS['save_rootdir']."/queue";
	
	unlink("$queue_dir/$md5_url");
}



function q_getPageFromQueue($md5_url)
{
	$queue_dir = $GLOBALS['save_rootdir']."/queue";
	$serialized = file_get_contents("$queue_dir/$md5_url");

	return unserialize($serialized);
}


function q_getQueue()
{
	$queues = new Queues();
	$queues->Load('queue');
	
	return $queues;
}

/*function q_saveResult($task,$id,$content,$serialize=true)
{
	if ($serialize) {
		$content = serialize($content);
	}	
	
	file_put_contents($GLOBALS['save_rootdir']."/result/$task".'_'.$id,$content);
}*/


/*function q_saveGlobalResult($task,$content,$serialize=true)
 {
		if ($serialize) {
			$content = serialize($content);
		}	
		
		file_put_contents($GLOBALS['save_rootdir']."/global/$task.txt",$content."\n",FILE_APPEND);
 }*/


/*function q_savePageLinks($page_id,$md5_pageurl,$urls,$site_id,$url_site)
 {
   		$sql_link = "";

   		// Ajoute les valeurs SQL des liens
    	foreach ($urls as $url =>$data) 
    	{
    		$md5_url = md5($url);
    		$sql_link .= sprintf("(%d,'%s','%s',%d,'%s',0)\n",$page_id,$md5_url,$page_id,myaddslashes($url),$site_id,$url_site);
			
    	}
		
		file_put_contents($GLOBALS['save_rootdir']."/global/$md5_pageurl.txt",$sql_link);
 }*/


 
?>
