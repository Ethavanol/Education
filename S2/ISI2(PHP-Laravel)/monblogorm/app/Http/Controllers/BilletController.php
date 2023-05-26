<?php

namespace App\Http\Controllers;

use App\Http\Requests\StoreBilletRequest;
use App\Http\Requests\UpdateBilletRequest;
use App\Models\Billet;
use Illuminate\Support\Facades\Log;

class BilletController extends Controller
{
    /**
     * Display a listing of the resource.
     */
    public function index()
    {
        try{
            $billets = Billet::all();
        }
        catch(\Illuminate\Database\QueryException $e){
            Log::error('Erreur accès base de données');
            return view('errors.unavaible');
        }
        return view('index', compact('billets'));
    }

    /**
     * Show the form for creating a new resource.
     */
    public function create()
    {
        //
    }

    /**
     * Store a newly created resource in storage.
     */
    public function store(StoreBilletRequest $request)
    {
        //
    }

    /**
     * Display the specified resource.
     */
    public function show(Billet $billet)
    {
        //
        $commentaires = $billet->commentaires;
        return view('vBillet', compact('billet', 'commentaires'));
    }

    /**
     * Show the form for editing the specified resource.
     */
    public function edit(Billet $billet)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     */
    public function update(UpdateBilletRequest $request, Billet $billet)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     */
    public function destroy(Billet $billet)
    {
        //
    }
}
