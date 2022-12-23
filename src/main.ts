import resetSheet from "./assets/css/reset.css";
import styleSheet from "./assets/css/style.css";
import initConfigForm from "./configuration";
import {initSession} from "./session";

export interface WordPair {
    word: string;
    definition: string;
}

export enum Sections {
    CONFIG,
    SESSION,
    RESULTS,
}

function createStyle(content: string): HTMLStyleElement{
    const $styleElement = document.createElement("style");
    $styleElement.innerHTML = content;
    return $styleElement;
}

function injectCSS() {
    const $head = document.querySelector("head");
    //$head?.insertAdjacentElement("beforeend", createStyle(resetSheet));
    $head?.insertAdjacentElement("beforeend", createStyle(styleSheet));
}

export function navigate(section: Sections){
    const $sections = document.querySelectorAll("section");
    $sections.forEach(s => s.classList.add("hidden"));
    $sections[section].classList.remove("hidden");
}

export function main() {
    injectCSS();
    initConfigForm();
    initSession();
}

document.addEventListener("DOMContentLoaded", main);
