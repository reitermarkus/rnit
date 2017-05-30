((fn) => {
  if (document.addEventListener) {
    document.addEventListener('DOMContentLoaded', fn, false)
    document.addEventListener('touchstart', function() {}, true)
  } else if (window.addEventListener) {
    window.addEventListener('load', fn, false)
    window.addEventListener('touchstart', function() {}, true)
  }
})(() => {
  document.querySelector('button[type="submit"]').addEventListener('click', (e) => {
    e.preventDefault()
    var request = new Request('./login.php', {
      method: 'post',
      body: new FormData(document.querySelector('form'))
    })

    fetch(request).then((response) => {
     return response.json()
    }).then((output) => {
      document.querySelector('.output-wrapper').innerHTML = ''

      if(output.error === undefined) {
        if(localStorage.getItem(output.spy) !== null) {
          document.querySelector('.output-wrapper').innerHTML += localStorage.getItem(output.spy)
        } else {
          document.querySelector('.output-wrapper').innerHTML += 
            '<p>First login on: ' + output.timestamp + ' with ip: ' + output.ip + '</p>'
        }

        localStorage.setItem(output.spy, '<p>Last login on: ' + output.timestamp + ' with ip: ' + output.ip + '</p>')
        document.querySelector('.output-wrapper').innerHTML += output.spys
      } else {
        document.querySelector('.output-wrapper').innerHTML += output.error
      }
    })
  }, true);
})