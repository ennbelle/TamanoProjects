/* 
 * Author: Annabelle Tamano
 * Project: CHEM-X
 * Purpose: Split Chemical Formula for calculations
 */

function splitArr() {
    var og=document.getElementById("formula");
    var arr=og.split(/(?=[A-Z])/);
    document.write(arr);
}


