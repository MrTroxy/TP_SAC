var boisChoisi;
var temperature;


// Fonction qui permet d'obtenir le nom du système (actualisée toutes les secondes)

// Appel un GET sur le serveur pour récupérer des données d'un API REST | Fonction getAllWood
window.addEventListener("load", getAllWoodOptions());
function getAllWoodOptions(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    console.log(description);
                    
                    for(var i = 0; i < description.length; i++)
                    {
                        var nomBois = description[i].name;
                        var idBois = description[i].id;
                        document.getElementById("typeBois_ListBox_Select").innerHTML += "<option value='" + idBois + "'>" + nomBois + "</option>";
                        document.getElementById("typeBois_ListBox_Select").style.color = "red";
                    }
                    
                    document.getElementById("typeBois_ListBox_Select").addEventListener("change", getCaracteristiqueBois);
                }
            }
        };
    xhttp.open("GET", "getAllWoodOptions", true);
    xhttp.send();
}

setInterval(function getFromEsp_TemperatureSensor()
{ //
    var xhttp = new XMLHttpRequest();
   
    xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
            document.getElementById("temp").innerHTML = this.responseText;
            temperature = this.responseText;
            
        }
    };
    xhttp.open("GET", "getTemperatureSensor", true);
    xhttp.send();
}, 3000);

    // Demande le nom du système afin de l’afficher dans la vue HTML

    // function getFromESP_getNom () {
    //     var xhttp = new XMLHttpRequest();
    //     xhttp.onreadystatechange = function () {
    //     if (this.readyState == 4 && this.status == 200) {
    //     document.getElementById("nom").innerHTML = this.responseText;
    //     }
    //     };
    //     xhttp.open("GET", "getNomEsp", true);
    //     xhttp.send();
    //    }


       // Fonction récupérer les infos de l'API Bois

function getInfoWood()
{
    var x = document.getElementById('typeBois_ListBox_Select');
    
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4 && this.status == 200)
        {
            var arrayOfStrings = JSON.parse(this.responseText);
            for (i = 0; i < arrayOfStrings.results.length; i++)
            {
                if (x.value == arrayOfStrings.results[i].id)
                {
                    boisChoisi = arrayOfStrings.results[i];
                    document.getElementById('nom').innerHTML = arrayOfStrings.results[i].bois;
                    document.getElementById('nom2').innerHTML = arrayOfStrings.results[i].bois;
                    document.getElementById('typeBois').innerHTML = arrayOfStrings.results[i].typeBois;
                    document.getElementById('origine').innerHTML = arrayOfStrings.results[i].origine;
                    document.getElementById('tempsSechage').innerHTML = arrayOfStrings.results[i].tempsSechage;
                    document.getElementById('tempsSechage2').innerHTML = arrayOfStrings.results[i].tempsSechage;
                    document.getElementById('tempMin').innerHTML = arrayOfStrings.results[i].tempMin;
                    document.getElementById('tempMin2').innerHTML = arrayOfStrings.results[i].tempMin;
                }
             }
         }
    }
    xhttp.open("GET", "getAllWoodOptions", true);
    xhttp.send();
}

// Fonction pour démarrer le compte à rebour du four

function demarrageFour()
{
    var i = 0;
    var temp = parseInt(temperature);
    console.log(boisChoisi);
    if( temp >= boisChoisi.tempMin) {
       var timer = setInterval(function(){
            i++
            document.getElementById("timer").innerHTML = i;
            console.log(i);
            if(i == boisChoisi.tempsSechage){
                clearInterval(timer);
            }
            
        }, 1000);
    }
    else
    {
        console.log('non');
    }
};
