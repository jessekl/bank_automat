-- MySQL dump 10.13  Distrib 8.0.19, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bank_automat
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `idaccount` int NOT NULL AUTO_INCREMENT,
  `iduser` int NOT NULL,
  `accountNumber` varchar(45) NOT NULL,
  `creditLimit` decimal(10,2) NOT NULL,
  `balance` decimal(10,2) NOT NULL,
  `currentDebt` decimal(10,2) NOT NULL,
  PRIMARY KEY (`idaccount`),
  UNIQUE KEY `accountNumber_UNIQUE` (`accountNumber`),
  KEY `fk_account_user1_idx` (`iduser`),
  CONSTRAINT `fk_account_user1` FOREIGN KEY (`iduser`) REFERENCES `user` (`iduser`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (5,1,'FI1298573',12.00,976.00,0.00),(7,1,'FI12985725',5000.00,1000.00,0.00),(8,1,'FI129857',3000.00,765.00,2000.00),(9,6,'FI12985731513512',5000.00,1000.00,0.00),(10,7,'FI1298573151351212',5000.00,1000.00,0.00);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL AUTO_INCREMENT,
  `idaccount` int NOT NULL,
  `pinNumber` varchar(255) NOT NULL,
  `cardNumber` varchar(255) NOT NULL,
  `cardExpiration` date NOT NULL,
  `cardReader` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `cardNumber_UNIQUE` (`cardNumber`),
  KEY `fk_card_account1_idx` (`idaccount`),
  CONSTRAINT `fk_card_account1` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,5,'1250','155','1000-01-01','15'),(3,8,'$2b$10$7BXuWlv1KMdcI831Lz/3i.oKaFkWNVNAegv1n56zZuSK.AhH1pVGy','951815','1001-01-01','24t4'),(4,8,'$2b$10$zVH/lXqh6.s0bqWLGjbu8.nBpbJ7YUgY2q2mGZTe0dRIkdTX/UYTW','06000623A6','1001-01-01','24t4'),(6,9,'$2b$10$PUzRyUe3S/lsaPr8ZDEC6u6JUNkoBttwkZ7zrr.mt6IMWPyWYZ1mS','0600062090','1001-01-01','24t4');
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transactionhistory`
--

DROP TABLE IF EXISTS `transactionhistory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transactionhistory` (
  `idtransactionHistory` int NOT NULL AUTO_INCREMENT,
  `idaccount` int NOT NULL,
  `date` date NOT NULL,
  `amount` int NOT NULL,
  PRIMARY KEY (`idtransactionHistory`),
  KEY `fk_transactionHistory_account1_idx` (`idaccount`),
  CONSTRAINT `fk_transactionHistory_account1` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`)
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactionhistory`
--

LOCK TABLES `transactionhistory` WRITE;
/*!40000 ALTER TABLE `transactionhistory` DISABLE KEYS */;
INSERT INTO `transactionhistory` VALUES (2,5,'1000-01-01',200),(3,5,'1000-01-01',200),(4,5,'1000-01-01',200),(5,5,'1000-01-01',200),(6,5,'1000-01-01',200),(7,5,'1001-01-01',20),(8,7,'1001-01-01',20),(9,7,'1001-01-01',20),(10,8,'2024-04-23',10),(11,8,'2024-04-23',10),(12,8,'2024-04-23',10),(13,8,'2024-04-24',5),(14,8,'2024-04-24',5),(15,8,'2024-04-24',5),(16,8,'2024-04-24',5),(17,8,'2024-04-24',5),(18,8,'2024-04-24',5),(19,8,'2024-04-24',5),(20,8,'2024-04-24',5),(21,8,'2024-04-24',5),(22,8,'2024-04-24',5),(23,8,'2024-04-24',5),(24,8,'2024-04-24',5),(25,8,'2024-04-24',5),(26,8,'2024-04-24',10),(27,8,'2024-04-24',100),(28,8,'2024-04-25',10),(29,8,'2024-04-25',5);
/*!40000 ALTER TABLE `transactionhistory` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `iduser` int NOT NULL AUTO_INCREMENT,
  `fName` varchar(45) NOT NULL,
  `lName` varchar(45) NOT NULL,
  `personalId` varchar(45) DEFAULT NULL,
  `phoneNumber` varchar(45) DEFAULT NULL,
  `Address` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`iduser`),
  UNIQUE KEY `personalId_UNIQUE` (`personalId`),
  UNIQUE KEY `phoneNumber_UNIQUE` (`phoneNumber`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (1,'Aku','Ankka',NULL,NULL,NULL),(2,'Matti','Meikäläinen','0329324-325','0401234567',NULL),(3,'matti','meikäläinen','32059','309530295',NULL),(6,'Minni','meikäläinen','320595325','3095302953252',NULL),(7,'Jaa','jaa','32059532524','309530295325212',NULL);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-04-25 15:36:41
