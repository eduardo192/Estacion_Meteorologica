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
    let nomcul = document.getElementById('nomcul').value;
    let clima = document.getElementById('clima').value;
    let nomCiudad = document.getElementById('nomCiudad').value;
    let nomEstado = document.getElementById('nomEstado').value;
    let fecha = document.getElementById('fecha').value;

    console.log(nomNave);
    const datos = {
        Cultivo: nomcul,
        Clima: clima,
        Ciudad:nomCiudad,
        Estado: nomEstado,
        Fecha: fecha
    };
    db.ref(nomNave ).set(datos);

}

obtenerDatos();

function obtenerDatos(){
    const tabla = document.getElementById('tabla');
    let starCountRef = firebase.database().ref()
    starCountRef.on('value', function(snapshot) {
        
        const d = snapshot.val();
        //console.log(d);
        for (const key in d) {
            
            console.log(d[key]);
            tabla.innerHTML += 
            `<tr>
                <th scope="row">${key}</th>
                <td>${d[key].Cultivo}</td>
                <td>${d[key].Clima}</td>
                <td>${d[key].Ciudad}</td>
                <td>${d[key].Estado}</td>
                <td>${d[key].Fecha}</td>
                <td><button class="btn btn-danger">Eliminar</button></td>
                <td><button class="btn btn-warning" >Editar</button></td>
            </tr>`;
        }
    });
    
}

function borrarNaves(){

}