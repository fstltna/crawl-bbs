/<pre class="code">/,/<\/pre>/ !d;
s/.*<pre class="code">//;
s/<\/pre>.*//;
s/&lt;/</g;
s/&gt;/>/g;
s/&quot;/"/g;
s/&#0*39;/'/g;
s/&amp;/&/g;
s/ *$//;
