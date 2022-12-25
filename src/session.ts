import { navigate, Sections, WordPair } from "./main";
import {showResults} from "./results";

let StartTime = 0;
let IsFlipping = false;
let IsFlipped = false;

let CurrentWord: WordPair = {
    word: "",
    definition: "",
};
let Words: Array<WordPair> = [];

let EasyWords: Array<WordPair> = [];
let HardWords: Array<WordPair> = [];

const $Card = <HTMLDivElement>document.querySelector("#card");
const $Counts = <HTMLParagraphElement> document.querySelector("#counts");

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

function showDefinition() {
    setCardText(CurrentWord.definition, "p");
}

function endFlipping() {
    $Card.classList.remove("flip");

    if (IsFlipped) {
        showDefinition();
    } else {
        showWord(CurrentWord);
    }
}

function showWord(pair: WordPair) {
    CurrentWord = pair;
    setCardText(CurrentWord.word, "h3");
    $Counts.innerHTML = `${HardWords.length} - ${EasyWords.length}`;
}

function nextWord(){
    if (Words.length > 1){
        Words.shift();
        showWord(Words[0]);
    }else{
        showResults(EasyWords,HardWords);
    }
}

function pressedKnownButton(e: Event) {
    EasyWords.push(CurrentWord);
    nextWord();
}

function pressedUnknownButton(e: Event) {
    HardWords.push(CurrentWord);
    nextWord();
}

export function startSession(pairs: Array<WordPair>) {
    navigate(Sections.SESSION);
    StartTime = Date.now();
    EasyWords = [];
    HardWords = [];
    Words = pairs;
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

    const $timer = <HTMLParagraphElement>document.querySelector("#timer");
    setInterval(() => {
        const diff = (Date.now() - StartTime) / (1000 * 60);
        $timer.innerHTML = `${diff.toFixed(0)} min`;
    }, 1000);

    const $unknownButton = <HTMLButtonElement> document.querySelector("#unknown-button");
    $unknownButton.addEventListener("click", pressedUnknownButton);

    const $knownButton = <HTMLButtonElement> document.querySelector("#known-button");
    $knownButton.addEventListener("click", pressedKnownButton);

    const $cancelButton = <HTMLButtonElement> document.querySelector("#cancel-button");
    $cancelButton.addEventListener("click", () => {
        navigate(Sections.CONFIG);
    });
}
