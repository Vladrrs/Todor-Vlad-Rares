#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WRONG_GUESSES 6
#define MAX_WORD_LENGTH 20

// List of Romanian words for the game
const char *words[] = {
    "casa", "masina", "pom", "floare", "carte", "scaun", "masa", "pisica", "caine", "soare",
    "luna", "stea", "apa", "foc", "pamant", "cer", "mare", "munte", "padure", "gradina",
    "fruct", "legume", "mancare", "bautura", "om", "femeie", "copil", "parinte", "frate", "sora",
    "prieten", "scoala", "profesor", "elev", "scris", "citit", "muzica", "film", "televizor", "computer",
    "telefon", "strada", "oras", "tara", "lume", "timp", "zi", "noapte", "dimineata", "seara",
    "iarna", "vara", "primavara", "toamna", "iubire", "fericire", "tristete", "furie", "bucurie",
    "paine", "lapte", "carne", "peste", "mere", "pere", "portocale", "banane", "rosii", "cartofi",
    "ceapa", "usturoi", "sare", "piper", "zahar", "cafea", "ceai", "suc", "vin", "bere",
    "supa", "salata", "friptura", "paste", "orez", "mazare", "fasole", "morcov", "varza", "conopida",
    "broccoli", "sparanghel", "ciuperci", "oua", "branza", "unt", "miere", "iaurt", "smantana", "crema",
    "prajitura", "tort", "placinta", "biscuiti", "ciocolata", "inghetata", "nuci", "alune", "migdale", "stafide",
    "smochine", "curmale", "lamaie", "grepfrut", "ananas", "mango", "papaya", "kiwi", "avocado", "struguri",
    "capsuni", "zmeura", "afine", "mure", "coacaze", "visine", "cirese", "prune", "piersici", "caise",
    "gutui", "rodii", "pepene", "lubenita", "dovleac", "dovlecel", "vinete", "ardei", "porumb", "grau",
    "orz", "ovaz", "graunte", "seminte", "plante", "animale", "pasari", "pesti", "mamifere", "reptile",
    "insecte", "păsări", "fluturi", "albine", "furnici", "paianjeni", "melci", "limacși", "șerpi", "broaște",
    "șopârle", "cameleoni", "țestoase", "crocodili", "delfini", "balene", "foci", "lei", "tigri", "ursi",
    "lupi", "vulpi", "iepuri", "capre", "oi", "vaci", "cai", "porci", "gâște", "rațe", "curcani", "pui",
    "găini", "cocoși", "papagali", "canari", "peștișori", "caracatițe", "homari", "crabi", "scoici", "midii",
    "alge", "corali", "stele de mare", "meduze", "calmari", "sepie", "ton", "somon", "macrou", "hering",
    "sardine", "anșoa", "cod", "biban", "știucă", "caras", "crap", "somn", "lin", "păstrăv", "lostriță",
    "avioane", "trenuri", "autobuze", "camioane", "biciclete", "scutere", "barci", "vapoare", "avioane", "elicoptere",
    "rachete", "sateliți", "planete", "stele", "galaxii", "univers", "atomi", "molecule", "celule", "organe",
    "sisteme", "corp", "creier", "inima", "plamani", "ficat", "rinichi", "stomac", "intestine", "oase",
    "muşchi", "piele", "păr", "unghii", "dinți", "limba", "nas", "urechi", "ochi", "sprâncene",
    "gene", "obraji", "bărbie", "gât", "umeri", "brațe", "coate", "mâini", "degete", "picioare",
    "genunchi", "picioare", "talpa", "călcâie", "degete de la picioare", "cap", "frunte", "tâmple", "ceafă", "spate",
    "piept", "abdomen", "șolduri", "fese", "coapse", "gambe", "glezne", "labele", "palme", "podul palmei",
    "police", "arătător", "mijlociu", "inelar", "mic", "haluce", "deget mare de la picior", "deget mic", "talpă", "plantă",
    "culoare", "roșu", "albastru", "verde", "galben", "portocaliu", "roz", "violet", "negru", "alb",
    "gri", "maro", "bej", "turcoaz", "indigo", "magenta", "cian", "lămâie", "măsliniu", "coral",
    "lavandă", "ciocolatiu", "auriu", "argintiu", "platină", "cupru", "bronz", "sidef", "perlat", "opalescent",
    "iridescent", "fluorescent", "fosforescent", "transparent", "translucid", "opac", "lucios", "mat", "brillant", "satenat",
    "velur", "catifea", "mătase", "bumbac", "lână", "in", "mătase", "viscoză", "poliestru", "nailon", "acrilic",
    "spandex", "elastin", "cașmir", "angora", "mohair", "alpaca", "lama", "vicuna", "șuviță", "fire", "ață",
    "fir", "cordon", "șnur", "sfoară", "frânghie", "lanț", "cabluri", "conducte", "țevi", "tuburi", "bare",
    "plăci", "foi", "panouri", "blocuri", "cuburi", "sfere", "cilindri", "conuri", "piramide", "prisme",
    "octaedre", "icosaedre", "dodecaedre", "tetraedre", "hexaedre", "pentaedre", "triunghiuri", "pătrate", "dreptunghiuri", "romburi",
    "trapeze", "paralelograme", "cercuri", "elipse", "hiperbole", "parabole", "spirale", "zigzag", "ondulat", "dantelat",
    "franjurat", "crestat", "zimțat", "festonat", "brodat", "împletit", "înodat", "legat", "sudat", "lipit",
    "cimentat", "mortar", "ipsos", "var", "clei", "adeziv", "bandă", "cârlig", "piuneze", "șuruburi",
    "piulițe", "nituri", "știfturi", "bolțuri", "șurubelnițe", "ciocane", "clești", "foarfeci", "seceri", "coase",
    "topoare", "ferăstraie", "burghie", "rindea", "ciocan pneumatic", "presă", "mașini", "utilaje", "aparate", "dispozitive",
    "instrumente", "scule", "unelte", "echipamente", "instalații", "sisteme", "rețele", "circuite", "plăci de circuit", "microcipuri",
    "transistoare", "rezistoare", "condensatoare", "inductoare", "diode", "triode", "pentode", "tetrode", "tiristoare", "varistoare",
    "potențiometre", "relee", "comutatoare", "întrerupătoare", "prize", "ștecăr", "mufe", "conectori", "cablu", "fir",
    "antene", "paratrăsnete", "izolații", "conductori", "semiconductori", "superconductori", "izolanți", "dieletric", "feromagnetic", "paramagnetic",
    "diamagnetic", "antiferromagnetic", "ferrimagnetic", "piezoelectric", "piroelectric", "electrostrictiv", "magnetostrictiv", "termoelectric", "fotoelectric", "electroluminiscent",
    "fotoluminiscent", "cathodoluminiscent", "chemiluminiscent", "bioluminescent", "radioluminescent", "triboluminescent", "sonoluminescent", "mechanoluminescent", "triboelectric", "piezoelectric",
    "electrokinetic", "elektroosmotic", "electroforetic", "dielectric", "capacitive", "inductive", "resistive", "ohmic", "non-ohmic", "superconducting",
    "semiconducting", "insulating", "conducting", "metallic", "ionic", "covalent", "molecular", "atomic", "nuclear", "subatomic",
    "quarks", "leptoni", "bosoni", "fermioni", "neutroni", "protoni", "electroni", "neutrino", "muoni", "tauoni",
    "pioni", "kaoni", "lambda", "sigma", "xi", "omega", "delta", "rho", "phi", "eta",
    "theta", "iota", "kappa", "lambda", "mu", "nu", "xi", "omicron", "pi", "rho",
    "sigma", "tau", "upsilon", "phi", "chi", "psi", "omega", "alpha", "beta", "gamma",
    "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu", "nu",
    "xi", "omicron", "pi", "rho", "sigma", "tau", "upsilon", "phi", "chi", "psi",
    "omega", "alef", "bet", "gimel", "dalet", "he", "vav", "zayin", "het", "tet",
    "yod", "kaf", "lamed", "mem", "nun", "samekh", "ayin", "pe", "tsadi", "qof",
    "resh", "shin", "tav", "aleph", "beth", "gimel", "daleth", "heth", "waw", "zayin",
    "heth", "teth", "yodh", "kaph", "lamedh", "mem", "nun", "samekh", "ayin", "pe",
    "tsade", "qoph", "resh", "shin", "tav", "a", "b", "c", "d", "e",
    "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
    "p", "q", "r", "s", "t", "u", "v", "w", "x", "y",
    "z", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii",
    "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss",
    "tt", "uu", "vv", "ww", "xx", "yy", "zz", "aaa", "bbb", "ccc",
    "ddd", "eee", "fff", "ggg", "hhh", "iii", "jjj", "kkk", "lll", "mmm",
    "nnn", "ooo", "ppp", "qqq", "rrr", "sss", "ttt", "uuu", "vvv", "www",
    "xxx", "yyy", "zzz", "aaaa", "bbbb", "cccc", "dddd", "eeee", "ffff", "gggg",
    "hhhh", "iiii", "jjjj", "kkkk", "llll", "mmmm", "nnnn", "oooo", "pppp", "qqqq",
    "rrrr", "ssss", "tttt", "uuuu", "vvvv", "wwww", "xxxx", "yyyy", "zzzz"
};
#define NUM_WORDS (sizeof(words) / sizeof(words[0]))

// Function to choose a random word
const char* chooseRandomWord() {
    int index = rand() % NUM_WORDS;
    return words[index];
}

// Function to initialize the display array with underscores
void initializeDisplay(char display[], int length) {
    for (int i = 0; i < length; i++) {
        display[i] = '_';
    }
    display[length] = '\0';
}

// Function to display the current state of the word
void displayWord(const char display[]) {
    printf("Word: %s\n", display);
}

// Function to check if a letter is in the word and update display
int checkLetter(const char word[], char display[], char letter, int wordLength) {
    int found = 0;
    for (int i = 0; i < wordLength; i++) {
        if (tolower(word[i]) == tolower(letter)) {
            display[i] = word[i];
            found = 1;
        }
    }
    return found;
}

// Function to check if the word is fully guessed
int isWordGuessed(const char display[], int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        if (display[i] == '_') {
            return 0;
        }
    }
    return 1;
}

// Function to display the hangman based on wrong guesses
void displayHangman(int wrongGuesses) {
    printf("\n");
    switch (wrongGuesses) {
        case 0:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 1:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 2:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 3:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 4:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 5:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /    |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 6:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" / \\  |\n");
            printf("      |\n");
            printf("=========\n");
            break;
    }
}

int main() {
    srand(time(NULL));
    const char* word = chooseRandomWord();
    int wordLength = strlen(word);
    char display[MAX_WORD_LENGTH + 1];
    initializeDisplay(display, wordLength);

    int wrongGuesses = 0;
    char guessedLetters[26] = {0}; // To track guessed letters
    int guessedCount = 0;

    printf("Welcome to Hangman!\n");
    printf("You have %d wrong guesses allowed.\n", MAX_WRONG_GUESSES);

    while (wrongGuesses < MAX_WRONG_GUESSES && !isWordGuessed(display, wordLength)) {
        displayHangman(wrongGuesses);
        displayWord(display);
        printf("Guessed letters: ");
        for (int i = 0; i < guessedCount; i++) {
            printf("%c ", guessedLetters[i]);
        }
        printf("\n");

        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        // Check if already guessed
        int alreadyGuessed = 0;
        for (int i = 0; i < guessedCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }
        if (alreadyGuessed) {
            printf("You already guessed that letter!\n");
            continue;
        }

        guessedLetters[guessedCount++] = guess;

        if (!checkLetter(word, display, guess, wordLength)) {
            wrongGuesses++;
            printf("Wrong guess! %d wrong guesses left.\n", MAX_WRONG_GUESSES - wrongGuesses);
        } else {
            printf("Good guess!\n");
        }
    }

    displayHangman(wrongGuesses);
    displayWord(display);

    if (isWordGuessed(display, wordLength)) {
        printf("Congratulations! You won! The word was: %s\n", word);
    } else {
        printf("Sorry, you lost! The word was: %s\n", word);
    }

    return 0;
}