{{>HEADER}}
{{>PAGE_HEADER}}
<div id="wrapper"> {{! Siempre necesito los dos DIVs. }}
	<div id="content">
		<h1>Config</h1>
		<form action="" method="GET">
			{{#VAR_SEC}}
			<p>
				<b>{{VAR_NAME:h}}:</b>
				<span id="{{VAR_NAME:h}}.desc">
					<span id="{{VAR_NAME:h}}.val">{{VAR_VALUE:h}}</span>
					<a href="#" onclick="editVar('{{VAR_NAME:h:j}}')">editar</a>
				</span>
				<span id="{{VAR_NAME:h}}.cancelEdit" style="display:none">
					<a href="#" onclick="cancelEditVar('{{VAR_NAME:h:j}}')">cancelar</a>
				</span>
			</p>
			{{/VAR_SEC}}
			<p>
				<input id="saveButton" type="submit" value="Guardar cambios" disabled="true" /> 
				<input id="cancelButton" type="button" value="Cancelar" onclick="cancelAllEditVars()" disabled="true" />
			</p>
		</form>
	</div>
</div>
{{>MENU}}
{{>FOOTER}}
