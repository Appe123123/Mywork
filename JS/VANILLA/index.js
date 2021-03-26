//JS의 선언은 let , const, (var)이 있음 
//JS에서는 const를 주로 사용하는것을 권장 !


const title = document.querySelector("#title");
title.style.color = "blue";
title.innerHTML = "HI!";

function handleClick() {
    title.style.color = "red";
}

window.addEventListener("click", handleClick);
