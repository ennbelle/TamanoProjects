<!DOCTYPE html>
<!--
    Author  : Annabelle Tamano
    Project : CHEM-X Website
    Purpose : By the elements page
-->
<html>
    <head>
        <title>Explore the Elements</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="../style.css">
    </head>
        
    <body>
        <div id="topbar">
           <img src="../img/logo.png" alt="Chem-X Logo"/> 
        </div>
        <div><a href="../index.html">HOME</a>  |  EXPLORE THE ELEMENTS  |  <a href="calcweight.php">MOLECULAR WEIGHT CALCULATOR</a></div>
        
        <div id="container">
            <h2>Explore the Elements</h2>
            <p> Find more generic information on an element by searching by its atomic number (1-118).</p>
            <form action="" method="POST">
                <input type="text" name="search" id="search">
                <input type="submit" name="submit" value="Search">
            </form>
            
            <h3>Results</h3>
            
        <?php
        $servername = "localhost";
        $username = "root";
        $password = "";
        $dbname = "chemtable";
        
        session_start();
        $search_val=$_POST["search"];
        // Create connection
        $conn = mysqli_connect($servername, $username, $password, $dbname);
        // Check connection
        if (!$conn) {
            die("Connection failed: " . mysqli_connect_error());
        } else {
            $sql="SELECT name, formula, weight FROM entity_element WHERE idelement LIKE '%$search_val%'";
            $res = mysqli_query($conn, $sql);
            
            if( $row = mysqli_fetch_assoc($res) ) {
                echo "Element: " . $row['name']."<br>Symbol: " . $row['formula']. "<br>Molecular Weight: " . $row['weight']. " g/mol<br />";
            } else {
                echo "No results.";
            }
        }
        
        mysqli_close($conn);
        ?>
            
        </div>
        
    </body>
</html>