$(function() {

    $('#btn-on').click(function(){
        $.ajax({
            url: "/led-on"
        });
    });

    $('#btn-off').click(function(){
        $.ajax({
            url: "/led-off"
        });
    });
});