((fn) => {
  if (document.addEventListener) {
    document.addEventListener('DOMContentLoaded', fn, false)
    document.addEventListener('touchstart', function() {}, true);
  } else if (window.addEventListener) {
    window.addEventListener('load', fn, false);
    window.addEventListener('touchstart', function() {}, true);
  }
})(() => {
  document.querySelector('button[type="submit"]').addEventListener('click', (e) => {
    e.preventDefault()
    var request = new Request('./login.php', {
      method: 'post',
      body: new FormData(document.querySelector('form'))
    })

    fetch(request).then((response) => {
     return response.text()
    }).then((output) => {
      document.querySelector('.output-wrapper').innerHTML = ''
      document.querySelector('.output-wrapper').innerHTML += output
    })
  }, true);
})