<!doctype html>
<html lang="fr">
    <head>
        <meta chraset="UTF-8" />
        <link rel="stylesheet" href="{{ URL::asset('style.css') }}" />
        <title>Mon blog</title>
    </head>
    <body>
        <div id="global">
            <header>
                <a href="{{ route('billets.index') }}"><h1 id="titreBlog">Mon Blog</h1></a>
                <p>Je vous souhaite la bienvenue sur ce modeste blog.</p>
            </header>
            <div id="contenu">
                @yield('contenu')
            </div>
            <footer id="piedBlog">
                Blog réalisé avec PHP, HTML et CSS.
            </footer>
        </div>
    </body>
</html>
