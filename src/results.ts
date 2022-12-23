import {navigate, Sections, WordPair} from "./main";
import {renderTable} from "./utils";

export function showResults(easy: Array<WordPair>, hard: Array<WordPair>){
    navigate(Sections.RESULTS);

    const totalWords = easy.length + hard.length;

    const $perc = <HTMLSpanElement> document.querySelector("#percentage");
    $perc.innerHTML = ((easy.length / totalWords)*100).toFixed(0);

    const $easyTable = <HTMLTableElement> document.querySelector("#easy-table");
    renderTable($easyTable, easy);

    const $hardTable = <HTMLTableElement> document.querySelector("#hard-table");
    renderTable($hardTable, hard);

    console.log(easy,hard);
}
