<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Commentaire extends Model
{
    use HasFactory;

    protected $fillable=[
        'COM_date',
        'COM_AUTEUR',
        'COM_CONTENU',
        'billet_id',
    ];

    public $timestamps = false;

    public function billet(){
        return $this->belongsTo(Billet::class);
    }
}
