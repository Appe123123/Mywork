//JS의 선언은 let , const, (var)이 있음 
//JS에서는 const를 주로 사용하는것을 권장 !


const title = document.querySelector("#title");
//title.style.color = "blue";
//title.innerHTML = "HI!";

const CLICKED_CLASS = "clicked";

function handleClick() {
    const hasClass = title.classList.contains(CLICKED_CLASS)
    if(!hasClass) {
        title.classList.add(CLICKED_CLASS);
    }
    else {
        title.classList.remove(CLICKED_CLASS);
    }
}

window.addEventListener("click", handleClick);
