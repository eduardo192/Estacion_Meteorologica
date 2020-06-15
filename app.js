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

let Creada = false;

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
    db.ref(nomNave).set(datos);
    Creada = true

}

const tabla = document.getElementById('tabla');
let starCountRef = db.ref()
starCountRef.on('value', function(snapshot) {
    tabla.innerHTML = '';
    const d = snapshot.val();
    //console.log(d);

    
    for (const key in d) {
        console.log(key);
        console.log(d[key]);    
        if(d[key].Cultivo != undefined || d[key].Clima != undefined || d[key].Ciudad != undefined ){
            tabla.innerHTML += 
            `<tr>
                <th scope="row">${key}</th>
                <td>${d[key].Cultivo}</td>
                <td>${d[key].Clima}</td>
                <td>${d[key].Ciudad}</td>
                <td>${d[key].Estado}</td>
                <td>${d[key].Fecha}</td>
                <td>${d[key].Sensores.Temperatura}</td>
                <td>${d[key].Sensores.Humedad}</td>
                <td><button class="btn btn-danger" onclick="borrar('${key}')">Eliminar</button></td>
                <td><button class="btn btn-warning" onclick="editar('${key}','${d[key].Cultivo}', '${d[key].Clima}', '${d[key].Ciudad}', '${d[key].Estado}', '${d[key].Fecha}')">Editar</button></td>
            </tr>`;
        }     
        
    }
});

function borrar(key) {console.log('borrar: ' + key);
    db.ref(key).remove();
}
function editar(key, cultivo, clima, ciudad, estado, fecha) {


    console.log('editar: ' + key);
    const boton = document.getElementById('btnAgregar');
    let nave = document.getElementById('nomNave');
    nave.setAttribute('disabled', "true");
    document.getElementById('nomNave').value = key;
    document.getElementById('nomcul').value = cultivo;
    document.getElementById('clima').value = clima;
    document.getElementById('nomCiudad').value = ciudad;
    document.getElementById('nomEstado').value = estado;
    document.getElementById('fecha').value = fecha;

    boton.innerHTML = 'Editar';

    boton.onclick = function () {
        let nomcul = document.getElementById('nomcul').value;
        let clima = document.getElementById('clima').value;
        let nomCiudad = document.getElementById('nomCiudad').value;
        let nomEstado = document.getElementById('nomEstado').value;
        let fecha = document.getElementById('fecha').value;
        
        const datos = {
            Cultivo: nomcul,
            Clima: clima,
            Ciudad:nomCiudad,
            Estado: nomEstado,
            Fecha: fecha
        };

        db.ref(key).update(datos);
    }
}