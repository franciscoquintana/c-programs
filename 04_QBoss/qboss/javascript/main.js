var lienzo
var Xw = 700
var Yw = 450

function cambia(c) {
    return [ Xw + c[0], Yw - c[1] ]
}

function punto(p) {
    var cords = cambia(p)
    var r = 25

    lienzo.beginPath()
    lienzo.arc(cords[0],cords[1], r-10 , 0, 2 * Math.PI, false)
    lienzo.fillStyle = "#00CCCC"
    lienzo.fill()
    lienzo.arc(cords[0],cords[1], r , 0, 2 * Math.PI, false)
    lienzo.stroke()

}

function main() {
    lienzo = document.getElementById("cloth").getContext("2d")

    punto([0,0])
    punto([10,10])
}
