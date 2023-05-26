@extends('layout')
@section('contenu')
    @foreach($billets as $billet)
        <article>
            <header>
                <h1 class="titreBillet">
                    <a href="{{ route('billets.show',$billet->id) }}">{{ $billet->BIL_TITRE }}</a>
                </h1>
                <time>{{ $billet->BIL_DATE }}</time>
                <p>dans :
                    @php
                        $counter = 0;
                    @endphp
                    @foreach($billet->categories as $categorie)
                        {{ $categorie->CAT_NOM }}
                        @php
                            $counter++;
                        @endphp
                        @if(count($billet->categories) > $counter)
                            /
                        @endif
                    @endforeach
                </p>
            </header>
            <p> {{ $billet->BIL_CONTENU }}</p>
        </article>
        <hr/>
    @endforeach
@endsection