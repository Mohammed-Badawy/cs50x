// blink title
function blink()
{
    let title = document.querySelector('#rubber');
    if (title.style.visibility == 'hidden')
    {
        title.style.visibility = 'visible';
    }
    else
    {
        title.style.visibility = 'hidden';
    }
}

// blink every 500ms
window.setInterval(blink, 1000);