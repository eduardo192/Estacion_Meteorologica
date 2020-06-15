const firebaseConfig = {
    apiKey: "AIzaSyDWfxwXG0QhhnBpUGBugptz3AXnK1yem-w",
    authDomain: "estacion-86bac.firebaseapp.com",
    databaseURL: "https://estacion-86bac.firebaseio.com",
    storageBucket: "estacion-86bac.appspot.com"
}

//INICIAR FIREBASE
firebase.initializeApp(firebaseConfig);

const db = firebase.database(); 
console.log(db)
//AGREGAR
function crearNave(){
    let nomNave = document.getElementById('nomNave').value;
    console.log(nomNave);
    db.ref(nomNave + "/Sensores").set({
        
    });
}