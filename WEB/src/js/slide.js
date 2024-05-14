//Cortesía de fumono studios
var slideIndex = 1;
var slides = [];
showSlides(slideIndex);

function plusSlides(n) {
    showSlides(slideIndex += n);
}

function showSlides(n) {
    var i;
    slides = document.getElementsByClassName("imgen");
    if (n > slides.length) {slideIndex = 1}    
    if (n < 1) {slideIndex = slides.length}
    for (i = 0; i < slides.length; i++) {
        slides[i].classList.remove("visible");  
    }
    slides[slideIndex-1].classList.add("visible");  
}

function currentSlide(n) {
    for (i = 0; i < slides.length; i++) {
        slides[i].classList.remove("visible");  
    }
    slides[n-1].classList.add("visible");  
}