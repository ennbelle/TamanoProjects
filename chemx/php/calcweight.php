<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <title>Molecular Weight Calculator</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="../style.css">
    </head>
    <body>
        <div id="topbar">
           <img src="../img/logo.png" alt="Chem-X Logo"/> 
        </div>
        
        <div><a href="../index.html">HOME</a>  |  <a href="elements.php">EXPLORE THE ELEMENTS</a>  |  MOLECULAR WEIGHT CALCULATOR</div>
        
        <div id="container">
            <h2>Molecular Weight Calculator</h2>
            <p>Enter Chemical Formula</p>
               <form action="" method="POST">
                <input type="text" name="formula" id="formula">
                <input type="submit" name="submit" value="Calculate" onclick='splitArr()'>
            </form>
            
            <script>
                function splitArr() {
                    var og=document.getElementById("formula");
                    var arr=og.split(/(?=[A-Z])/);
                    document.write(arr);
                }
                </script>
                
                <p>This page is still a work in progress. Form is not completely functional...</p>
        </div>
        
        
    </body>
</html>

