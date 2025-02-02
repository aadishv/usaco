function check() {
  console.log("ggg");
  var elements = document.getElementsByTagName("h2");
  const text = `//${elements[0].innerHTML}\n//${elements[1].innerHTML}\n// ${window.location.href}`;
  elements[0].addEventListener("click", () => {
    navigator.clipboard.writeText(text);
    const old = elements[0].innerHTML;
    elements[0].innerHTML = "copied!";
    setTimeout(() => {
      elements[0].innerHTML = old;
    }, 700);
  });
  var year = elements[0].innerHTML.slice(6, 11);
  var month = elements[0].innerHTML.slice(12, 15);
  if (month.includes("US")) {
    month = "USO";
  }

  var importantStuff = elements[1].innerHTML.slice(12);
  var titles = document.getElementsByTagName("title");
  titles[0].innerHTML = `${importantStuff}`;
  var thing = document.getElementsByTagName("select");
  thing[1].value = "7";
}
document.addEventListener("DOMContentLoaded", () => {
  document.getElementsByTagName("img")[0].outerHTML =
    `<img height="50px" border="0px"></div>`;
  console.log(window.location);
  if (window.location.href.includes("viewproblem")) {
    check();
  }
});
