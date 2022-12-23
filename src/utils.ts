import {WordPair} from "./main";

export function renderTable($tbody: HTMLTableElement, words: Array<WordPair>) {
    $tbody.innerHTML = "";

    words.forEach((p) => {
        const html = `
            <tr>
                <td>${p.word}</td>
                <td>${p.definition}</td>
            </tr>
        `;
        $tbody.insertAdjacentHTML("beforeend", html);
    });
}
