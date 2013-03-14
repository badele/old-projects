<?php
/*
 * Created on 13 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 


	mysql_connect ($mysql_host, $mysql_user, $mysql_password);
    mysql_select_db ($database);
    
    /*function db_disableIndex($tablename) 
    {
    	db_query("ALTER TABLE $tablename DISABLE KEYS;");
    }

    function db_enableIndex() 
    {
    	db_query("ALTER TABLE $tablename ENABLE KEYS;");
    }*/


	function db_mysql_fetch_rows($result) {
		$results=array();

		if ($result) {
			while ($row = mysql_fetch_array($result)) {
				array_push($results, $row);
			}
		}
		
		return $results;
	}

	function db_mysql_fetch_object($result,$classname) {
		$results=array();

		if ($result) {
			while ($row = mysql_fetch_object($result,$classname)) {
				array_push($results, $row);
			}
		}
		
		return $results;
	}


	function db_query($query,$try_error=1)
	{
		if ($GLOBALS['debug_db']) print "$query\n<br>";
		 
		$result = mysql_query($query);
		
		if ($try_error) {
			$error = mysql_error();
			if ($error!="") {
				//@trigger_error("$error - $query");
				throw new Exception("$error - $query");
			}
		}
		
		return $result;
	}

    function db_Begin() 
    {
    	db_query("START TRANSACTION;");
    }

    function db_Commit() 
    {
    	db_query("COMMIT;");
    }

    function db_Rollback() 
    {
    	db_query("ROLLBACK;");
    }


	function db_Close()
	{
		mysql_close();
	}

    
    function getlink($url)
    {
    	
    	$url = myaddslashes($url);
    	$result = db_query ("select * from page where url='$url'");
    	
		$row = mysql_fetch_assoc($result);
		
		return $row;
    	
		    	
    }


	function db_incrementCounter($counter_name,$value)
	{
		db_query("select value from counter where name='$counter_name' for update");
		db_query("update counter set value=value+$value where name='$counter_name'");
	}

	function db_getincrementCounter($counter_name)
	{
		$result = db_query("select value from counter where name='$counter_name'");
		$result = mysql_fetch_row($result);
		
		return $result[0];
		
	}
    function getSite($site) 
    {
		$result = db_query("select * from site where url='$site' limit 1");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
    }

    function getSiteID($id) 
    {
		$result = db_query("select * from site where site_id=$id");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
    }



    
?>