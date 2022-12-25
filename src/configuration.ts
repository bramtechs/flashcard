import queryString from "query-string";
import {navigate, Sections, WordPair} from "./main";
import {initSession, startSession} from "./session";
import {renderTable} from "./utils";

const Placeholder = "Goedemorgen; Good morning\nBonne journee; Have a good day\nありがとう; Thank you"

export function showHideParseError(visible: boolean) {
    const $error = <HTMLLabelElement>document.querySelector("form .error");
    if (visible) {
        $error.classList.remove("hidden");
    } else {
        $error.classList.add("hidden");
    }
}

export function parseWords(input: string): [boolean, Array<WordPair>] {
    input = input.replaceAll("\r", "");
    let ok = true;
    const slices = input.split("\n");

    let result: Array<WordPair> = [];

    slices.forEach((line) => {
        line = line.trim();
        if (line.length === 0) {
            return;
        }

        const segments = line.split(";");
        if (segments !== undefined && segments.length == 2) {
            const pair = <WordPair>{
                word: segments[0],
                definition: segments[1],
            };
            result.push(pair);
        } else {
            ok = false;
        }
    });

    console.log(result);
    return [ok, result];
}

export function wordAreaParseContent($area: HTMLTextAreaElement) {
    console.log($area.value);
    const result = parseWords($area.value);


    showHideParseError(false);
    if (result[0] === true) {
        const $tbody = <HTMLTableElement>document.querySelector("#preview tbody");
        renderTable($tbody,result[1]);
    } else {
        showHideParseError(true);
    }
}

export function generateURL($area: HTMLTextAreaElement){
    // update query string
    const result = queryString.stringify({"input":$area.value}).toString();
    window.location.search = result;
}

export function prepareSession(){
    const $wordArea = <HTMLTextAreaElement>document.querySelector("#words");
    const result = parseWords($wordArea.value);
    if (result[0]){
        const pairs = result[1];
        startSession(pairs); 
        console.log(pairs);
    }else{
        alert("Invalid parsed words");
    }
}

export default function initConfigForm() {
    navigate(Sections.CONFIG);

    const $wordArea = <HTMLTextAreaElement>document.querySelector("#words");
    $wordArea.addEventListener("change", (_) => wordAreaParseContent($wordArea));

    // check query strings
    const parsed = queryString.parse(location.search);
    if (parsed["input"] !== undefined){
        $wordArea.value = <string> parsed["input"];
    }
    else if ($wordArea.value.length === 0) {
        $wordArea.value = Placeholder;
    }
    wordAreaParseContent($wordArea);

    const $startButton = <HTMLInputElement> document.querySelector("#configuration input[type='submit']");
    $startButton.addEventListener("click", (e) => {
        e.preventDefault();
        prepareSession();
    });

    const $genURLButton = <HTMLInputElement> document.querySelector("#gen-url");
    $genURLButton.addEventListener("click", (e) => {
        e.preventDefault();
        generateURL($wordArea);
    });
}
