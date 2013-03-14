-- MySQL dump 10.11
--
-- Host: localhost    Database: crawler
-- ------------------------------------------------------
-- Server version	5.0.60

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `link`
--

DROP TABLE IF EXISTS `link`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `link` (
  `link_id` int(11) NOT NULL auto_increment,
  `link` varchar(255) character set latin1 collate latin1_general_ci NOT NULL COMMENT 'Lien',
  `state_taskpage` tinyint(1) NOT NULL default '0' COMMENT 'Indique si l''on a ajouter les liens dans la table page en fonction des sites',
  PRIMARY KEY  (`link_id`),
  KEY `idx_link` (`link`),
  KEY `idx_state_taskpage` (`state_taskpage`)
) ENGINE=MyISAM AUTO_INCREMENT=1456235 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `link_from`
--

DROP TABLE IF EXISTS `link_from`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `link_from` (
  `from_page_id` int(11) NOT NULL COMMENT 'La page qui contient le mot-lien',
  `word_id` int(11) NOT NULL COMMENT 'le mot-lien',
  `link_id` int(11) NOT NULL COMMENT 'Pointe vers un lien',
  `to_page_id` int(11) default NULL,
  PRIMARY KEY  USING BTREE (`from_page_id`,`word_id`,`link_id`),
  KEY `id_from_pageid` (`from_page_id`),
  KEY `idx_link_id` (`link_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `link_to`
--

DROP TABLE IF EXISTS `link_to`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `link_to` (
  `page_id` int(11) NOT NULL,
  `link_id` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  PRIMARY KEY  USING BTREE (`page_id`,`link_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `page`
--

DROP TABLE IF EXISTS `page`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `page` (
  `url` varchar(255) character set latin1 collate latin1_general_ci NOT NULL,
  `title` varchar(200) character set latin1 collate latin1_general_ci default NULL,
  `size` float default NULL,
  `md5` varchar(32) character set latin1 collate latin1_general_ci default NULL,
  `site_id` int(11) NOT NULL default '0',
  `lastcrawl` date default NULL,
  `state_crawled` tinyint(1) NOT NULL default '0',
  `page_id` int(11) NOT NULL auto_increment,
  `state_linked` tinyint(1) default '0',
  `state_updated` tinyint(1) default '0',
  `state_keyword` tinyint(1) default '0',
  `count_backlink` int(11) NOT NULL,
  `link_id` int(11) NOT NULL COMMENT 'Indique le lien qui à créer cette page, evite le page.url=link.link',
  PRIMARY KEY  USING BTREE (`page_id`),
  KEY `url` (`url`),
  KEY `md5key` (`md5`),
  KEY `site_id` (`site_id`),
  KEY `state_crawled` (`state_crawled`),
  KEY `state_linked` (`state_linked`),
  KEY `idx_backlink` (`count_backlink`),
  KEY `idx_keyword_crawled` (`state_crawled`,`state_keyword`),
  KEY `idx_link_id` (`link_id`)
) ENGINE=MyISAM AUTO_INCREMENT=851798 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `page_data`
--

DROP TABLE IF EXISTS `page_data`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `page_data` (
  `page_id` int(11) NOT NULL,
  `html` mediumtext character set latin1 collate latin1_general_ci,
  `text` mediumtext character set latin1 collate latin1_general_ci,
  `header` mediumtext character set latin1 collate latin1_general_ci,
  `http_code` int(11) default '0',
  PRIMARY KEY  USING BTREE (`page_id`)
) ENGINE=MyISAM AUTO_INCREMENT=851798 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `site`
--

DROP TABLE IF EXISTS `site`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `site` (
  `site_id` int(11) NOT NULL auto_increment,
  `url` varchar(255) character set latin1 collate latin1_general_ci default NULL,
  `depth` int(11) default '2',
  `site` varchar(255) character set latin1 collate latin1_general_ci NOT NULL,
  `last_crawled` datetime NOT NULL default '0000-00-00 00:00:00',
  `disable` tinyint(1) NOT NULL,
  PRIMARY KEY  (`site_id`),
  KEY `lastcrawled` (`last_crawled`)
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `stat_link_from`
--

DROP TABLE IF EXISTS `stat_link_from`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `stat_link_from` (
  `to_page_id` int(11) NOT NULL default '0',
  `word_id` int(11) NOT NULL COMMENT 'le mot-lien',
  `count` int(11) NOT NULL,
  PRIMARY KEY  (`to_page_id`,`word_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `temp_link_from`
--

DROP TABLE IF EXISTS `temp_link_from`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `temp_link_from` (
  `page_id` int(11) NOT NULL,
  `link` varchar(255) character set latin1 collate latin1_general_ci NOT NULL,
  `word` varchar(255) character set latin1 collate latin1_general_ci NOT NULL,
  KEY `idx_page_id` USING BTREE (`page_id`),
  KEY `idx_word` (`word`),
  KEY `idx_link` (`link`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `temp_link_from_link`
--

DROP TABLE IF EXISTS `temp_link_from_link`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `temp_link_from_link` (
  `link` varchar(255) collate latin1_general_ci NOT NULL,
  `temp_id` int(11) NOT NULL,
  PRIMARY KEY  (`temp_id`),
  KEY `idx_link` (`link`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `temp_link_from_page_id`
--

DROP TABLE IF EXISTS `temp_link_from_page_id`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `temp_link_from_page_id` (
  `page_id` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `temp_link_from_word`
--

DROP TABLE IF EXISTS `temp_link_from_word`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `temp_link_from_word` (
  `word` varchar(255) collate latin1_general_ci NOT NULL,
  `temp_id` int(11) NOT NULL,
  KEY `idx_word` (`word`),
  KEY `idx_temp_id` (`temp_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `temp_link_to`
--

DROP TABLE IF EXISTS `temp_link_to`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `temp_link_to` (
  `link` varchar(255) character set latin1 collate latin1_general_ci NOT NULL COMMENT 'Lien',
  `count` int(11) NOT NULL,
  `page_id` int(11) NOT NULL,
  KEY `idx_link` (`link`),
  KEY `idx_page_id` (`page_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `word`
--

DROP TABLE IF EXISTS `word`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `word` (
  `word_id` int(11) NOT NULL auto_increment,
  `word` varchar(255) character set latin1 collate latin1_general_ci NOT NULL,
  PRIMARY KEY  (`word_id`),
  UNIQUE KEY `idx_word` (`word`)
) ENGINE=MyISAM AUTO_INCREMENT=571849 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `worded`
--

DROP TABLE IF EXISTS `worded`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `worded` (
  `page_id` int(11) NOT NULL,
  `word_id` int(11) NOT NULL,
  `density` double NOT NULL,
  `weight` double NOT NULL,
  PRIMARY KEY  (`page_id`,`word_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2008-07-24 20:09:20
