import { WordPair } from "./main";

let StartTime = 0;
let IsFlipping = false;
let IsFlipped = false;
let CurrentWord: WordPair | null = null;

const $Card = <HTMLDivElement>document.querySelector("#card");

function startFlipping() {
    $Card.classList.add("flip");
}

function setCardText(text: string, tag: string) {
    $Card.innerHTML = "";
    const html = `
        <${tag}>
            ${text}
        </${tag}>
    `;
    $Card.insertAdjacentHTML("beforeend", html);
}

function showDefinition(){
    if (CurrentWord == null) return;
    setCardText(CurrentWord.definition,"p");
}

function endFlipping() {
    $Card.classList.remove("flip");

    if (CurrentWord === null) {
        console.log("no word");
        return;
    }

    if (IsFlipped) {
        showDefinition();
    } else {
        showWord(CurrentWord);
    }
}

function showWord(pair: WordPair) {
    CurrentWord = pair;
    setCardText(CurrentWord.word,"h3");
}

export function startSession(pairs: Array<WordPair>) {
    StartTime = Date.now();
    showWord(pairs[0]);
}

export function initSession() {
    $Card.addEventListener("click", () => {
        if (!IsFlipping) {
            IsFlipping = true;
            IsFlipped = !IsFlipped;
            startFlipping();
            setTimeout(() => {
                IsFlipping = false;
                endFlipping();
            }, 300);
        }
    });

    const $timer = <HTMLParagraphElement> document.querySelector("#timer");
    setInterval(() => {
        const diff = (Date.now() - StartTime) / (1000*60);
        $timer.innerHTML = `${diff.toFixed(0)} min`;
    },1000);
}

