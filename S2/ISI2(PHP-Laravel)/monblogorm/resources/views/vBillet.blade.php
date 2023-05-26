@extends('layout')
@section('contenu')
<article>
        <header>
            <h1 class="titreBillet">{{ $billet->BIL_TITRE }}</h1>
            <time>{{ $billet->BIL_DATE }}</time>
        </header>
        <p> {{ $billet->BIL_CONTENU }}</p>
    </article>
    <hr/>
    @if (count($commentaires) > 0)
        <header>
            <h1 id="titresReponses">Réponses à {{ $billet->BIL_TITRE }}</h1>
        </header>
        @foreach($commentaires as $commentaire)
            <p>{{ $commentaire->COM_AUTEUR }} dit :</p>
            <p>{{ $commentaire->COM_CONTENU }}</p>
        @endforeach
    @else
        <header>
            <h1 id="titresReponses">Il n'y a pas de réponses à ce billet</h1>
        </header>
    @endif
@endsection