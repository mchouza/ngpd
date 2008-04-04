//
// Copyright (c) 2008, Mariano M. Chouza
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * The names of the contributors may not be used to endorse or promote
//      products derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

//=============================================================================
// config.js
//-----------------------------------------------------------------------------
// Creado por Mariano M. Chouza | Empezado el 3 de abril de 2008
//=============================================================================

// Cantidad de edits que están abiertas
var editsPending = 0;

// Cambio la cantidad de edits pendientes
function changeEditsPending(delta)
{
	// Cambio la variable
	editsPending += delta;
	
	// Si es positivo, puedo guardar o cancelar
	if (editsPending > 0)
	{
		// Activo ambos edits
		document.getElementById('saveButton').disabled = false;
		document.getElementById('cancelButton').disabled = false;
	}
	else
	{
		// Es cero, desactivo a ambos
		document.getElementById('saveButton').disabled = true;
		document.getElementById('cancelButton').disabled = true;
	}
}

// Construye el control para editar a la variable
function makeEditVarControl(varName)
{
	// Creo el control
	var ret = document.createElement('input');
	
	// Le doy atributos
	ret.setAttribute('id', varName);
	ret.setAttribute('name', varName);
	ret.setAttribute('type', 'text');
	
	// Tiene el texto de la variable
	ret.setAttribute('value', 
		document.getElementById(varName + '.val').textContent);
	
	// Lo devuelvo
	return ret;
}

// Crea el cuadro para editar la variable, ocultando la descripción original
function editVar(varName)
{
	// Obtengo el texto a editar
	var varDesc = document.getElementById(varName + '.desc');
	
	// Oculto la descripción original
	varDesc.style.display = 'none';
	
	// Creo un cuadro de texto
	var editVarControl = makeEditVarControl(varName);
	
	// Lo agrego
	varDesc.parentNode.insertBefore(editVarControl, varDesc);
	
	// Muestro el link para cancelar
	document.getElementById(varName + '.cancelEdit').style.display = '';
	
	// Marco que es una más
	changeEditsPending(+1);
}

// Cancela la edición de una variable
function cancelEditVar(varName)
{		
	// Obtengo el edit
	var editVarControl = document.getElementById(varName);
	
	// Me fijo si ya está cancelada la edición
	if (editVarControl == null)
	{
		return;
	}
	
	// Obtengo la descripción
	var varDesc = document.getElementById(varName + '.desc');
	
	// Elimino el cuadro de texto
	editVarControl.parentNode.removeChild(editVarControl);
	
	// Oculto el link para cancelar
	document.getElementById(varName + '.cancelEdit').style.display = 'none';
	
	// Muestro la descripción
	varDesc.style.display = '';
	
	// Marco que es una menos
	changeEditsPending(-1);
}

// Cancela todas las ediciones que se estén realizando
function cancelAllEditVars()
{
	// Obtengo todas las inputs
	inputs = document.getElementsByTagName('input');
	for (var i = 0; i < inputs.length; i++)
	{
		// Si es un 'text', corresponde a una variable en edición
		if (inputs[i].getAttribute('type') == 'text')
		{
			// Cancelo la edición
			cancelEditVar(inputs[i].getAttribute('id'));
			
			// Como los números bajan en uno, el índice lo hace también
			i--;
		}
	}
}