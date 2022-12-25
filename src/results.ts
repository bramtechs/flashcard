import { navigate, Sections, WordPair } from "./main";
import { startSession } from "./session";
import { renderTable } from "./utils";

export function showResults(easy: Array<WordPair>, hard: Array<WordPair>) {
    navigate(Sections.RESULTS);

    const totalWords = easy.length + hard.length;

    const $perc = <HTMLSpanElement>document.querySelector("#percentage");
    $perc.innerHTML = ((easy.length / totalWords) * 100).toFixed(0);

    const $easyTable = <HTMLTableElement>document.querySelector("#easy-table");
    renderTable($easyTable, easy);

    const $hardTable = <HTMLTableElement>document.querySelector("#hard-table");
    renderTable($hardTable, hard);

    const $retryHardWords = <HTMLButtonElement>document.querySelector("#retry-hard");
    if (hard.length > 0){
        $retryHardWords.addEventListener("click", () => {
            startSession(hard);
        });
        $retryHardWords.disabled = false;
    }else{
        $retryHardWords.disabled = true;
    }


    const $retryAllWords = <HTMLButtonElement>document.querySelector("#retry-all");
    $retryAllWords.addEventListener("click", () => {
        let allWords = easy;
        allWords.push(...hard);
        startSession(allWords);
    });

    const $backButton = <HTMLButtonElement> document.querySelector("#back-button");
    $backButton.addEventListener("click", () => {
        navigate(Sections.CONFIG);
    });
}
