//Script de la funcionalidad del slider de imagenes
//Cortesía de fumono studios
var slideIndex = 1;
var slides = [];
showSlides(slideIndex);

//Mueve en n el numero del slide. Para 1 y -1 avanza siguiente y anterior.
function plusSlides(n) {
    showSlides(slideIndex += n);
}

//Activa las imagenes y establece una visible. Se llama al cargar este script.
function showSlides(n) {
    var i;
    slides = document.getElementsByClassName("imgen");
    if (n > slides.length) { slideIndex = 1 }
    if (n < 1) { slideIndex = slides.length }
    for (i = 0; i < slides.length; i++) {
        slides[i].classList.remove("visible");
    }
    slides[slideIndex - 1].classList.add("visible");
}

//Cambia la slide actual a n
function currentSlide(n) {
    for (i = 0; i < slides.length; i++) {
        slides[i].classList.remove("visible");
    }
    slides[n - 1].classList.add("visible");
}