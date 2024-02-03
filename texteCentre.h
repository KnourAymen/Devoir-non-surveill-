void centrerTexte(const char *texte)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int largeur_fenetre;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(console, &csbi))
    {
        largeur_fenetre = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    else
    {
        largeur_fenetre = 90;
    }

    int longueur_texte = strlen(texte);
    int espaces_gauche = (largeur_fenetre - longueur_texte) / 2;

    for (int i = 0; i < espaces_gauche; i++)
    {
        printf(" ");
    }

    printf("%s\n", texte);
}
